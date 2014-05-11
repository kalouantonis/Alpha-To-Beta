#ifndef EVENT_MANAGER_IMPL_H_
#define EVENT_MANAGER_IMPL_H_

#include <Events/EventManager.h>

#include <list>
#include <unordered_map>

const unsigned int NUM_QUEUES = 2;

class EventManager: public IEventManager
{
public:
    explicit EventManager(const char* pName, bool setAsGlobal);
    virtual ~EventManager();

    virtual bool addListener(const EventListenerDelegate &eventDelegate, EventType type) final;
    virtual bool removeListener(const EventListenerDelegate &eventDelegate, EventType type) final;

    virtual bool triggerEvent(const EventDataPtr &pEvent) const final;
    virtual bool queueEvent(const EventDataPtr &pEvent) final;
    virtual bool threadSafeQueueEvent(const EventDataPtr &pEvent) final;
    virtual bool abortEvent(EventType eventType, bool allOfType = false) final;

    // TODO: Implement maximum time for event processing.
    // We don't want to waste a load of time doing those
    virtual bool update(float deltaTime) final;

private:
    typedef std::list<EventListenerDelegate> EventListenerList;
    typedef std::unordered_map<EventType, EventListenerList> EventListenerMap;
    typedef std::list<EventDataPtr> EventQueue;

    EventListenerMap m_eventListeners;
    EventQueue m_queues[NUM_QUEUES];
    unsigned int m_activeQueue;

    ThreadSafeEventQueue m_realtimeEventQueue;
};

#endif // EVENT_MANAGER_IMPL_H_
