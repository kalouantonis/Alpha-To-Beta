#include <Events/EventManager.h>

#include <Resources/GenericObjectFactory.h>
#include <Utils/Logger.h>

#include <assert.h>

// Store a global event manager instance
static IEventManager* g_pEventManager = nullptr;
static GenericObjectFactory<EventType, IEventData> g_eventFactory;

template <class EventClass>
bool RegisterEvent()
{
    g_eventFactory.declare<EventClass>(EventClass::s_EventType);
}

EventDataPtr CreateEvent(EventType eventType)
{
    return EventDataPtr(
                g_eventFactory.create(eventType)
    );
}

IEventManager::IEventManager(const char *pName, bool setAsGlobal)
{
    if(setAsGlobal)
    {
        // If global, the manager is tasked with its setting the global static
        // instance to reference itself.
        if(g_pEventManager != nullptr)
        {
            CORE_ERROR("Attempting to create two global event managers. "
                       "The previous instance will be destroyed");
            delete g_pEventManager;
        }

        g_pEventManager = this;
    }
}

IEventManager::~IEventManager()
{
    // the event manager interface is tasked with the clean up of itself
    if(g_pEventManager == this)
    {
        // Set to null, no need for de-allocation, as the instance is already
        // in its destructor, meaning that it has already happened
        g_pEventManager = nullptr;
    }
}

IEventManager* IEventManager::get()
{
    assert(g_pEventManager != nullptr);
    return g_pEventManager;
}




