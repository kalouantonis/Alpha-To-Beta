#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

// Should probably fwd def
#include <Events/EventData.h>

#include <DataStructures/ConcurrentQueue.h>
#include <FastDelegate.h>

typedef ConcurrentQueue<EventDataPtr> ThreadSafeEventQueue;
typedef fastdelegate::FastDelegate1<EventDataPtr> EventListenerDelegate;

/**
 * @brief Register a new event for use with the event manager
 */
template <class EventClass>
bool RegisterEvent(void);
/**
 * @brief Create event using the event type
 * @param eventType
 * @return
 */
EventDataPtr CreateEvent(EventType eventType);

class IEventManager
{
public:
    /**
     * @brief Construct new event manager
     * @param pName Name to identify the manager as
     * @param setAsGlobal Should the manager be considered a global instance
     */
    explicit IEventManager(const char* pName, bool setAsGlobal);
    virtual ~IEventManager();

    virtual bool addListener(const EventListenerDelegate& eventDelegate, EventType type) = 0;
    virtual bool removeListener(const EventListenerDelegate& eventDelegate, EventType type) = 0;

    virtual bool triggerEvent(const EventDataPtr& pEvent) const = 0;
    virtual bool queueEvent(const EventDataPtr& pEvent) = 0;
    virtual bool threadSafeQueueEvent(const EventDataPtr& pEvent) = 0;

    virtual bool abortEvent(EventType eventType, bool allOfType = false) = 0;

    virtual bool update(float deltaTime) = 0;

    static IEventManager* get();
};

#endif // EVENTMANAGER_H_
