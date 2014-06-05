#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

#include <Utils/Logger.h>

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
    // get or create event table
    luabind::object eventTypeTable = LuaStateManager::get()->getGlobalVars()["EventType"];
    // Check if object has been initialized
    if(luabind::type(eventTypeTable) == LUA_TNIL)
    {
        luabind::settable(eventTypeTable, key, (double)type);
    }
    
    // Error checking
    assert(luabind::type(eventTypeTable) == LUA_TTABLE);
    assert(luabind::type(eventTypeTable[key]) == LUA_TNUMBER);
}

void ScriptEvent::addCreationFunction(EventType type, CreateEventForScriptFunctionType& creationFunction)
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
    // set event data to null
    // TODO: Check correctness. May not actually do what I said it does
    m_eventData.push(nullptr);
}
