#ifndef SCRIPT_EVENT_H
#define SCRIPT_EVENT_H

#include <Events/EventManager.h>

#include <luabind/object.hpp>

#include <functional>

class ScriptEvent;
typedef std::function<ScriptEvent*(void)> CreateEventForScriptFunctionType;

class ScriptEvent
{
public:
    ScriptEvent();
    /**
     * @brief Called when event is sent from C++ to script
     */
    const luabind::object& getEventData();
    /**
     * @brief Called when event is sent from script to C++
     * 
     * @param eventData Event data from script event
     * @return false if setting failed
     */
    bool setEventData(const luabind::object& eventData);

    /**
     * @brief Do not call this function directly. Use helpers instead
     * @details Static helper functions for registering events with to the script
     */
    static void registerEventTypeWithScript(const char* key, EventType type);
    static void addCreationFunction(EventType type, CreateEventForScriptFunctionType& creationFunction);
    static ScriptEvent* createEventFromScript(EventType event);

    
protected:
    virtual void buildEventData();
    virtual bool buildEventFromScript() { return false; }

    luabind::object m_eventData;

private:
    typedef std::map<EventType, CreateEventForScriptFunctionType> CreationFunctionsMap;
    static CreationFunctionsMap s_creationFunctions;

    bool m_bEventDataIsValid;
};

#endif // SCRIPT_EVENT_H
