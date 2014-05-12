#include <Events/EventManagerImpl.h>

#include <Utils/Logger.h>

#include <assert.h>

// Tag to log under
const char* LOG_TAG = "Events";

EventManager::EventManager(const char *pName, bool setAsGlobal)
    : IEventManager(pName, setAsGlobal)
    , m_activeQueue(0)
{

}

EventManager::~EventManager()
{

}

bool EventManager::addListener(const EventListenerDelegate &eventDelegate, EventType type)
{
    CORE_LOG(LOG_TAG, "Adding a delegate function for event type: "
             + std::to_string(type));

    EventListenerList& eventListenerList = m_eventListeners[type];
    // Check for double registering
    for(const auto& currentDelegate : eventListenerList)
    {
        if(eventDelegate == currentDelegate)
        {
            CORE_WARNING("Attempting to double register a delegate");
            return false;
        }
    }

    eventListenerList.push_back(eventDelegate);
    return true;
}

bool EventManager::removeListener(const EventListenerDelegate &eventDelegate, EventType type)
{
    CORE_LOG(LOG_TAG, "Removing delegate function from event type: " +
             std::to_string(type));

    // Success flag
    bool bSuccess = false;

    auto foundIt = m_eventListeners.find(type);
    if(foundIt != m_eventListeners.end())
    {
        EventListenerList& listeners = foundIt->second;
        // Use old school iterators, for erasing
        for(auto it = listeners.begin(); it != listeners.end(); ++it)
        {
            if(eventDelegate == (*it))
            {
                listeners.erase(it);
                bSuccess = true;
                // Dont need to continue, we know the same event can't be
                // registered twice
                break;
            }
        }
    }

    return bSuccess;
}

bool EventManager::triggerEvent(const EventDataPtr &pEvent) const
{
    CORE_LOG(LOG_TAG, "Triggering event " + std::string(pEvent->getName()));
    bool bProcessed = false;

    auto foundIt = m_eventListeners.find(pEvent->getEventType());
    if(foundIt != m_eventListeners.end())
    {
        const EventListenerList& eventListenerList = foundIt->second;
        for(const auto& listener : eventListenerList)
        {
            listener(pEvent);
            bProcessed = true;
        }
    }

    return bProcessed;
}

bool EventManager::queueEvent(const EventDataPtr &pEvent)
{
    assert(m_activeQueue >= 0);
    assert(m_activeQueue < NUM_QUEUES);

    if(!pEvent)
    {
        CORE_ERROR("Attempting to queue invalid event");
        return false;
    }

    CORE_LOG(LOG_TAG, "Queuing event: " + std::string(pEvent->getName()));

    auto foundIt = m_eventListeners.find(pEvent->getEventType());
    // Finding failed
    if(foundIt == m_eventListeners.end())
    {
        CORE_LOG(LOG_TAG, "Skipping event, no delegates to receive it: "
                 + std::string(pEvent->getName()));
        return false;
    }

    m_queues[m_activeQueue].push_back(pEvent);
    return true;
}

bool EventManager::threadSafeQueueEvent(const EventDataPtr &pEvent)
{
    m_realtimeEventQueue.push(pEvent);
    return true;
}

bool EventManager::abortEvent(EventType eventType, bool allOfType)
{
    assert(m_activeQueue >= 0);
    assert(m_activeQueue < NUM_QUEUES);

    bool bSuccess = false;

    auto foundIt = m_eventListeners.find(eventType);
    if(foundIt != m_eventListeners.end())
    {
        EventQueue& eventQueue = m_queues[m_activeQueue];

        auto it = eventQueue.begin();
        while(it != eventQueue.end())
        {
            // To remove an item from queue, the iterator is invalidated, so
            // we have to point to the next item
            auto removeIt = it;
            ++it;

            if((*removeIt)->getEventType() == eventType)
            {
                eventQueue.erase(removeIt);
                bSuccess = true;

                // If remove all of the same type, just iterate over the rest in the list
                // if not, break
                if(!allOfType)
                    break;
            }
        }
    }

    return bSuccess;
}

bool EventManager::update()
{
    // Not sure if this will work in a threaded environment.
    // The pop could continue without getting any real time event.
    // The while loop in the queue should handle this, but one can't be too
    // sure
    EventDataPtr pRealTimeEvent = m_realtimeEventQueue.pop();
    // Add events to current thread queue
    queueEvent(pRealTimeEvent);

    // Store currently active queue
    int queueToProcess = m_activeQueue;
    // Swap queue to next one, sort of like 2 buffers would
    m_activeQueue = (m_activeQueue + 1) % NUM_QUEUES;
    // clear the new queue
    m_queues[m_activeQueue].clear();

    EventQueue& processingQueue = m_queues[queueToProcess];

    while(!processingQueue.empty())
    {
        // Get next event in queue
        EventDataPtr pEvent = processingQueue.front();
        // Remove event from queue
        processingQueue.pop_front();

        EventType eventType = pEvent->getEventType();

        auto foundIt = m_eventListeners.find(eventType);
        if(foundIt != m_eventListeners.end())
        {
            const EventListenerList& eventListeners = foundIt->second;
            // Call each listener
            for(const auto& listener : eventListeners)
            {
                listener(pEvent);
            }
        }

        // TODO: Check to see if time ran out. If so, break from the loop
        // and log an error
    }

    bool bQueueFlushed = processingQueue.empty();
    if(!bQueueFlushed)
    {
        while(!processingQueue.empty())
        {
            // Remove all elements from previous processing queue
            EventDataPtr pEvent = processingQueue.back();
            processingQueue.pop_back();
            // Add to front of queue
            m_queues[m_activeQueue].push_front(pEvent);
        }
    }

    return bQueueFlushed;
}
