#include <Lua/ScriptExports.h>
#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

#include <Events/EventManager.h>

#include <Utils/Logger.h>

#include <set>

#include <luabind/scope.hpp>
#include <luabind/function.hpp>


// Script Event Listener ////////////////////////////////////////////////////////////////////////////////

class ScriptEventListener
{
public:
    /** @brief Create event listener using a lua function as a callback */
    explicit ScriptEventListener(EventType eventType, const luabind::object& scriptCallbackFunction);
    ~ScriptEventListener();
    
    EventListenerDelegate getDelegate()
    { 
        return fastdelegate::MakeDelegate(this, &ScriptEventListener::scriptEventDelegate); 
    }

private:
    void scriptEventDelegate(EventDataPtr pEvent);        

    luabind::object m_scriptCallbackFunction;
    EventType m_eventType;
};

ScriptEventListener::ScriptEventListener(EventType eventType, const luabind::object& scriptCallbackFunction)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Script Event Listener Manager ////////////////////////////////////////////////////////////////////////

class ScriptEventListenerManager
{
public:
    ~ScriptEventListenerManager();
    void addListener(ScriptEventListener* pListener);
    void destroyListener(ScriptEventListener* pListener);

private:
    std::set<ScriptEventListener*> m_listeners;
};

ScriptEventListenerManager::~ScriptEventListenerManager()
{
    // De-allocate all listeners
    for(auto pListener : m_listeners)
    {
        delete pListener;
    }

    // Clear the set
    m_listeners.clear();
}

void ScriptEventListenerManager::addListener(ScriptEventListener *pListener)
{
    m_listeners.insert(pListener);
}

void ScriptEventListenerManager::destroyListener(ScriptEventListener *pListener)
{
    auto findIt = m_listeners.find(pListener);
    if(findIt != m_listeners.end())
    {
        // Remove from set
        m_listeners.erase(findIt);
        delete pListener;
    }
    else
    {
        CORE_ERROR("Couldn't find script listener. This will likely cause a memory leak");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Internal Script Exports //////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ScriptExports
{

template<class CallerType, class RetType>
void registerExport(const char* luaFuncName, RetType (CallerType::*func)())
{
	// Bind to global lua state
	luabind::module(LuaStateManager::get()->getLuaState())
	[
		luabind::def(luaFuncName, func)		
	];
}

template<class RetType>
void registerExport(const char* luaFuncName, RetType (*func)())
{
	luabind::module(LuaStateManager::get()->getLuaState())
	[
		luabind::def(luaFuncName, func)
	];
}

}