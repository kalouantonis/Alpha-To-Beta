#ifndef JUMP_EVENT_H_
#define JUMP_EVENT_H_

#include <Lua/ScriptEvent.h>

// fwd defs
class DynamicBody;
class JumpBehaviour;

class JumpEvent: public ScriptEvent
{
public:
    static const EventType sEventType;

    JumpEvent();
    JumpEvent(DynamicBody* body, JumpBehaviour *jumpBehaviour);

    virtual EventType getEventType() const final { return sEventType; }
    virtual const char* getName() const final;

    DynamicBody* getBody() { return m_pBody; }
    const JumpBehaviour* getJumpBehaviour() const { return m_pJumpBehaviour; }
    JumpBehaviour* getJumpBehaviour() { return m_pJumpBehaviour; }


    EXPORT_FOR_SCRIPT_EVENT(JumpEvent)

private:
	virtual void buildEventData() final;
	virtual bool buildEventFromScript() final;

    DynamicBody* m_pBody;
    JumpBehaviour* m_pJumpBehaviour;
};

typedef std::shared_ptr<JumpEvent> JumpEventPtr;

#endif // JUMP_EVENT_H_
