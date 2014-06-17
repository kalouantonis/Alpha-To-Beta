#include <Lua/exports/EventExports.h>
#include <Lua/ScriptEvent.h>

#include <luabind/object.hpp>
#include <luabind/function.hpp>

#include <FastDelegate.h>

#include <set>

#include <Events/EventManager.h>

#include <Utils/Logger.h>

// Disable copying
#include <SFML/System/NonCopyable.hpp>

// Register core engine events
#include <Events/CollisionEvents.h>

namespace InternalScriptExports 
{

// ScriptEventListener//////////////////////////////////////////////////////////

class ScriptEventListener
{
public:
    explicit ScriptEventListener(EventType eventType, const luabind::adl::object& scriptCallbackFunction);
    ~ScriptEventListener();

    EventListenerDelegate getDelegate()
    {
        return fastdelegate::MakeDelegate(this, &ScriptEventListener::scriptEventDelegate);
    }

private:
    void scriptEventDelegate(EventDataPtr pEvent);

    luabind::adl::object m_scriptCallbackFunction;
    EventType m_eventType;
};

ScriptEventListener::ScriptEventListener(EventType eventType, const luabind::adl::object& scriptCallbackFunction)
    : m_scriptCallbackFunction(scriptCallbackFunction)
    , m_eventType(eventType)
{

}

ScriptEventListener::~ScriptEventListener()
{
    // Get global event manager instance
    IEventManager* pEventManager = IEventManager::get();
    if(pEventManager)
    {
        // Remove event listener from manager
        pEventManager->removeListener(getDelegate(), m_eventType);
    }
}

void ScriptEventListener::scriptEventDelegate(EventDataPtr pEvent)
{
    // Confirm that we are working with a function
    assert(luabind::type(m_scriptCallbackFunction) == LUA_TFUNCTION);

    // call the lua function
    std::shared_ptr<ScriptEvent> pScriptEvent = std::static_pointer_cast<ScriptEvent>(pEvent);
    // receive and call lua function, sending the event data as an argument
    // TODO: Ensure that callback is actually called
    luabind::call_function<void>(m_scriptCallbackFunction, pScriptEvent->getEventData());
}

////////////////////////////////////////////////////////////////////////////////

//ScriptEventListenerManager////////////////////////////////////////////////////

// NOTE: Probably don't need this
class ScriptEventListenerManager: private sf::NonCopyable // Dis-allow copying
{
public:
    ~ScriptEventListenerManager();
    void addListener(ScriptEventListener* pListener);
    void destroyListener(ScriptEventListener* pListener);

    /**
     *  Destroy all listeners
     */
    void destroyAll();

private:
    std::set<ScriptEventListener*> m_listeners;
};

ScriptEventListenerManager::~ScriptEventListenerManager()
{
    if(!m_listeners.empty())
        destroyAll();
}

void ScriptEventListenerManager::addListener(ScriptEventListener* pListener)
{
    m_listeners.insert(pListener);
}

void ScriptEventListenerManager::destroyListener(ScriptEventListener* pListener)
{
    auto findIt = m_listeners.find(pListener);
    if(findIt != m_listeners.end())
    {
        // Remove from set
        m_listeners.erase(findIt);
        // De-alloc
        delete pListener;
    }
    else
    {
        CORE_ERROR("Couldn't find script listener to destroy. This will likely cause a memory leak.");
    }
}

void ScriptEventListenerManager::destroyAll()
{
    // De-allocate all listeners
    for(auto pListener : m_listeners)
    {
        delete pListener;
    }

    m_listeners.clear();
}

////////////////////////////////////////////////////////////////////////////////

// Global script event manager instance
// Leave as smart pointer to protect against the forgetfullness of humans.
static std::unique_ptr<ScriptEventListenerManager> g_pScriptEventListenerManager = nullptr;

bool initEventExports()
{
    // Make sure we're not overwriting
    assert(g_pScriptEventListenerManager == nullptr);
    g_pScriptEventListenerManager = std::move(std::unique_ptr<ScriptEventListenerManager>(
            new ScriptEventListenerManager()
    ));
    return true;
}

void destroyEventExports()
{
    assert(g_pScriptEventListenerManager != nullptr);
    // De-alloc, desturctor should be called automatically, freeing listeners
    g_pScriptEventListenerManager = nullptr;
}

ListenerID registerEventListener(EventType eventType, const luabind::adl::object& luaCallbackFunc)
{
    assert(g_pScriptEventListenerManager != nullptr);

    // Validate that we're registering a function
    if(luabind::type(luaCallbackFunc) == LUA_TFUNCTION)
    {
        // Create c++ listener proxy and set it to listen for the event
        ScriptEventListener* pListener = new ScriptEventListener(eventType, luaCallbackFunc);
        g_pScriptEventListenerManager->addListener(pListener);
        IEventManager::get()->addListener(pListener->getDelegate(), eventType);

        // convert the pointer to an unsigned long and use it as the handle
        ListenerID handle = reinterpret_cast<ListenerID>(pListener);
        return handle;
    }

    CORE_ERROR("Attempting to register script event listener with invalid callback function");
    return 0;
}

void removeEventListener(ListenerID listenerId)
{
    assert(g_pScriptEventListenerManager != nullptr);
    // If 0, we're doing something wrong :)
    assert(listenerId != 0);

    // convert the listenerId in to a pointer
    ScriptEventListener* pListener = reinterpret_cast<ScriptEventListener*>(listenerId);
    g_pScriptEventListenerManager->destroyListener(pListener);
}

std::shared_ptr<ScriptEvent> buildEvent(EventType eventType, const luabind::adl::object& eventData)
{
    std::shared_ptr<ScriptEvent> pEvent(ScriptEvent::createEventFromScript(eventType));
    if(!pEvent)
    {
        // Return empty shared_ptr, will fall out of scope and be set to null
        return std::shared_ptr<ScriptEvent>();
    }

    if(!pEvent->setEventData(eventData))
    {
        return std::shared_ptr<ScriptEvent>();
    }

    return pEvent;
}

bool queueEvent(EventType eventType, const luabind::adl::object& eventData)
{
    std::shared_ptr<ScriptEvent> pEvent(
            buildEvent(eventType, eventData)
    );

    if(pEvent)
    {
        return IEventManager::get()->queueEvent(pEvent);
    }

    return false;
}

bool triggerEvent(EventType eventType, const luabind::adl::object& eventData)
{
    std::shared_ptr<ScriptEvent> pEvent(
            buildEvent(eventType, eventData)
    );

    if(pEvent)
    {
        return IEventManager::get()->triggerEvent(pEvent);
    }

    return false;
}

}
