#ifndef SCRIPT_EVENT_H
#define SCRIPT_EVENT_H

#include <Events/EventManager.h>

#include <LuaObject.h>
#include <unordered_map>

class ScriptEvent;
typedef ScriptEvent* (*CreateEventForScriptFunctionType)(void);

/** Register script using class type as event name */
#define REGISTER_SCRIPT_EVENT(eventClass, eventType) \
    ScriptEvent::registerEventTypeWithScript(#eventClass, eventType); \
    ScriptEvent::addCreationFunction(eventType, &eventClass::createEventFromScript);

/**
 * Modifies class definition, adding a method to create event from script
 */
#define EXPORT_FOR_SCRIPT_EVENT(eventClass) \
    public: \
        static ScriptEvent* createEventFromScript(void) \
        { \
            return new eventClass; \
        }

class ScriptEvent: public BaseEventData
{
public:
    ScriptEvent();
    /**
     * @brief Called when event is sent from C++ to script
     */
    LuaPlus::LuaObject getEventData();
    /**
     * @brief Called when event is sent from script to C++
     * 
     * @param eventData Event data from script event
     * @return false if setting failed
     */
    bool setEventData(const LuaPlus::LuaObject& eventData);

    /**
     * @brief Do not call this function directly. Use helpers instead
     * @details Static helper function for registering events to the script
     */
    static void registerEventTypeWithScript(const char* key, EventType type);
    static void addCreationFunction(EventType type, CreateEventForScriptFunctionType creationFunction);
    static ScriptEvent* createEventFromScript(EventType event);

    /**
     * Get the event type 
     */
    virtual EventType getEventType() const override { return sEventType; }
    virtual const char* getName() const override { return "ScriptEvent"; }

    static const EventType sEventType;
    
protected:
    /**
     * Prepare event data for use in script
     */
    virtual void buildEventData();
    virtual bool buildEventFromScript() { return false; }

    LuaPlus::LuaObject m_eventData;

private:
    typedef std::unordered_map<EventType, CreateEventForScriptFunctionType> CreationFunctionsMap;
    static CreationFunctionsMap s_creationFunctions;

    bool m_bEventDataIsValid;
};

#endif // SCRIPT_EVENT_H
