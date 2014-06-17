#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

#include <Utils/Logger.h>

const EventType ScriptEvent::sEventType = 0x82a1d091;

ScriptEvent::CreationFunctionsMap ScriptEvent::s_creationFunctions;

ScriptEvent::ScriptEvent()
    : m_bEventDataIsValid(false)
{

}

const luabind::object& ScriptEvent::getEventData() 
{
    if(!m_bEventDataIsValid)
    {
        // Create new event data 
        buildEventData();
        m_bEventDataIsValid = true;
    }

    return m_eventData;
}

bool ScriptEvent::setEventData(const luabind::object &eventData)
{
    m_eventData = eventData;
    // Build the event and check validity
    m_bEventDataIsValid = buildEventFromScript();
    return m_bEventDataIsValid;
}

void ScriptEvent::registerEventTypeWithScript(const char *key, EventType type)
{
    LuaStateManager* pStateManager = LuaStateManager::get();

    // get or create event table
    luabind::object eventTypeTable = pStateManager->getGlobalVars()["EventType"];
    // Check if object has been initialized
    if(luabind::type(eventTypeTable) == LUA_TNIL)
    {
        // Create new table
        eventTypeTable = luabind::newtable(pStateManager->getLuaState());
        // bind to global vars
        pStateManager->getGlobalVars()["EventType"] = eventTypeTable;
    }
    
    // Error checking
    assert(luabind::type(eventTypeTable) == LUA_TTABLE);
    assert(luabind::type(eventTypeTable[key]) == LUA_TNIL);

    // add entry
    luabind::settable(eventTypeTable, key, (double)type);
}

void ScriptEvent::addCreationFunction(EventType type, CreateEventForScriptFunctionType creationFunction)
{
    // Verify that creation function does not already exist
    assert(s_creationFunctions.find(type) == s_creationFunctions.end());
    s_creationFunctions.insert(std::make_pair(type, creationFunction));
}

ScriptEvent* ScriptEvent::createEventFromScript(EventType type)
{
    const auto findIt = s_creationFunctions.find(type);

    if(findIt != s_creationFunctions.end())
    {
        const CreateEventForScriptFunctionType& func = findIt->second;
        return func();
    }
    else
    {
        CORE_ERROR("Could not find event type: " + std::to_string(type));
        return nullptr;
    }
}

void ScriptEvent::buildEventData()
{
    // Set interpretter if it does not exist
    if(m_eventData.interpreter() == nullptr)
        m_eventData.push(LuaStateManager::get()->getLuaState());
}
