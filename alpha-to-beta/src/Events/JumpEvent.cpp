#include <Events/JumpEvent.h>

#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>

const EventType JumpEvent::sEventType = 0x8a2620ec;

JumpEvent::JumpEvent()
    : ScriptEvent()
    , m_pBody(nullptr)
    , m_pJumpBehaviour(nullptr)
{

}

JumpEvent::JumpEvent(DynamicBody* body, JumpBehaviour* jumpBehaviour)
    : ScriptEvent()
    , m_pBody(body)
    , m_pJumpBehaviour(jumpBehaviour)
{

}

const char *JumpEvent::getName() const
{
    return "JumpEvent";
}
