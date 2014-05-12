#ifndef EVENT_MANAGER_IMPL_H_
#define EVENT_MANAGER_IMPL_H_

#include <Events/EventManager.h>
#include <DataStructures/ConcurrentQueue.h>

#include <list>
#include <unordered_map>

/**
 * @brief Event manager implementation. Should not be used directly, except
 * instantiation. Use the IEventManager class in most cases.
 *
 * Used as a handle, reducing compile time dependencies and such
 */
class EventManager: public IEventManager
{
public:
    /**
     * @brief Maximum number of queues used by event manager.
     * Used like a buffer
     */
    static const unsigned int NUM_QUEUES = 2;

    explicit EventManager(const char* pName, bool setAsGlobal);
    virtual ~EventManager();

    virtual bool addListener(const EventListenerDelegate &eventDelegate, EventType type) final;
    virtual bool removeListener(const EventListenerDelegate &eventDelegate, EventType type) final;

    virtual bool triggerEvent(const EventDataPtr &pEvent) const final;
    virtual bool queueEvent(const EventDataPtr &pEvent) final;
    virtual bool threadSafeQueueEvent(const EventDataPtr &pEvent) final;
    virtual bool abortEvent(EventType eventType, bool allOfType = false) final;

    // TODO: Implement maximum time for event processing.
    // We don't want to waste a load of time on spamming events
    virtual bool update() final;

private:
    typedef std::list<EventListenerDelegate> EventListenerList;
    typedef std::unordered_map<EventType, EventListenerList> EventListenerMap;
    typedef std::list<EventDataPtr> EventQueue;
    typedef ConcurrentQueue<EventDataPtr> ThreadSafeEventQueue;

    /**
     * @brief Map of event types and a list of delegates
     */
    EventListenerMap m_eventListeners;
    /**
     * @brief Array of used event queues.
     */
    EventQueue m_queues[NUM_QUEUES];
    /**
     * @brief The currently active event queue
     */
    unsigned int m_activeQueue;

    /**
     * @brief Thread safe event queue, used in real time processes
     */
    ThreadSafeEventQueue m_realtimeEventQueue;
};

#endif // EVENT_MANAGER_IMPL_H_
