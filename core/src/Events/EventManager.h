#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

// Should probably fwd def
#include <Events/EventData.h>

#include <FastDelegate.h>

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

/**
 * @brief EventManager interface. This should be used in most cases.
 * Used as a handle to abstract away the details from users.
 */
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

    /**
     * @brief Add a new event listener
     * @param eventDelegate Listener delegate
     * @param type Type of event relating to listener
     * @return true if adding succeeded
     */
    virtual bool addListener(const EventListenerDelegate& eventDelegate, EventType type) = 0;
    /**
     * @brief Remove an existing event listener
     * @param eventDelegate Delegate listener
     * @param type Type of event relating to listener
     * @return true if removed successfully. Will fail if delegate does not exist
     */
    virtual bool removeListener(const EventListenerDelegate& eventDelegate, EventType type) = 0;

	virtual void removeAllListeners() = 0;

    /**
     * @brief Trigger the given event NOW. No queuing is used.
     * Use in time critical events.
     *
     * @param pEvent Event to trigger
     * @return true if triggering was successful.
     */
    virtual bool triggerEvent(const EventDataPtr& pEvent) const = 0;
    /**
     * @brief Add event to queue. Will be proceesed in the update() function
     * @param pEvent Event to queue
     * @return true if queuing was successful.
     */
    virtual bool queueEvent(const EventDataPtr& pEvent) = 0;
    /**
     * @brief Queue an event in a thread safe queue.
     * @param pEvent Event to queue
     * @return true if queuing was successful
     */
    virtual bool threadSafeQueueEvent(const EventDataPtr& pEvent) = 0;

    /**
     * @brief Abort given events. Will remove the from queue and will not be
     * processed by update() function
     * @param eventType Type to abort
     * @param allOfType If true, all events under the given type will be aborted
     * @return true if abort is a success.
     */
    virtual bool abortEvent(EventType eventType, bool allOfType = false) = 0;
	virtual void clearEventQueues(bool dispatch = false) = 0;

    /**
     * @brief Update the event queue. All pending events will be processed.
     * @return true if update success
     */
    virtual bool update() = 0;

    /**
     * @brief Get global event manager instance
     * @return Global event manager instance
     */
    static IEventManager* get();
};

typedef std::shared_ptr<IEventManager> EventManagerPtr;

#endif // EVENTMANAGER_H_
