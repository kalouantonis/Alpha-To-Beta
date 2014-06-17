#include <Events/Script.h>

#include <Events/JumpEvent.h>

void registerScriptEvents()
{
    REGISTER_SCRIPT_EVENT(JumpEvent, JumpEvent::sEventType);
}
