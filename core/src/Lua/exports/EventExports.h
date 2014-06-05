#ifndef EVENT_EXPORTS_H_
#define EVENT_EXPORTS_H_

#include <Events/EventData.h>

// FDW Defs ////////////////////////////////////////////////////////////////////
namespace luabind 
{
    namespace adl
    {
    class object;
    }
}
////////////////////////////////////////////////////////////////////////////////

namespace InternalScriptExports
{

typedef unsigned long ListenerID;


bool initEventExports();
void destroyEventExports();

ListenerID registerEventListener(EventType eventType, const luabind::adl::object& luaCallbackFunc);
void removeEventListener(ListenerID listenerId);
bool queueEvent(EventType eventType, const luabind::adl::object& eventData);
bool triggerEvent(EventType eventType, const luabind::adl::object& eventData);

}

#endif
