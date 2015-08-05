#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

#include <Utils/Logger.h>

const EventType ScriptEvent::sEventType = 0x82a1d091;

ScriptEvent::CreationFunctionsMap ScriptEvent::s_creationFunctions;

ScriptEvent::ScriptEvent()
    : m_bEventDataIsValid(false)
{

}

LuaPlus::LuaObject ScriptEvent::getEventData() 
{
    if(!m_bEventDataIsValid)
    {
        // Create new event data 
        buildEventData();
        m_bEventDataIsValid = true;
    }

    return m_eventData;
}

bool ScriptEvent::setEventData(const LuaPlus::LuaObject& eventData)
{
    m_eventData = eventData;
    // Build the event and check validity
    m_bEventDataIsValid = buildEventFromScript();
    return m_bEventDataIsValid;
}

void ScriptEvent::registerEventTypeWithScript(const char *key, EventType type)
{
    // get or create event table
    LuaPlus::LuaObject eventTypeTable = LuaStateManager::get()->getGlobalVars().GetByName("EventType");
    // Check if object has been initialized
    if(eventTypeTable.IsNil())
    {
        // Create new table
        eventTypeTable = LuaStateManager::get()->getGlobalVars().CreateTable("EventType");
    }
    
    // Error checking
    CORE_ASSERT(eventTypeTable.IsTable());
    CORE_ASSERT(eventTypeTable[key].IsNil());

    // add entry
    eventTypeTable.SetNumber(key, (double)type);
}

void ScriptEvent::addCreationFunction(EventType type, CreateEventForScriptFunctionType creationFunction)
{
    // Verify that creation function does not already exist
    CORE_ASSERT(s_creationFunctions.find(type) == s_creationFunctions.end());
    s_creationFunctions.insert(std::make_pair(type, creationFunction));
}

ScriptEvent* ScriptEvent::createEventFromScript(EventType type)
{
    // Get creation function for this event type
    const auto findIt = s_creationFunctions.find(type);

    if(findIt != s_creationFunctions.end())
    {
        const CreateEventForScriptFunctionType& func = findIt->second;
        // Create event
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
    m_eventData.AssignNil(LuaStateManager::get()->getLuaState());
}
