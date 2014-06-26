#ifndef EVENT_EXPORTS_H_
#define EVENT_EXPORTS_H_

#include <Events/EventData.h>

#include <LuaObject.h>

namespace InternalScriptExports
{

typedef unsigned long ListenerID;


bool initEventExports();
void destroyEventExports();

ListenerID registerEventListener(EventType eventType, LuaPlus::LuaObject luaCallbackFunc);
void removeEventListener(ListenerID listenerId);
bool queueEvent(EventType eventType, LuaPlus::LuaObject eventData);
bool triggerEvent(EventType eventType, LuaPlus::LuaObject eventData);

}

#endif
