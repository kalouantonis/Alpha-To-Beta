#ifndef JUMP_EVENT_H_
#define JUMP_EVENT_H_

#include <Events/EventData.h>

// fwd defs
class DynamicBody;
class JumpBehaviour;

class JumpEvent: public BaseEventData
{
public:
    static const EventType sEventType;

    JumpEvent(DynamicBody* body, const JumpBehaviour* jumpBehaviour);

    virtual EventType getEventType() const final { return sEventType; }
    virtual const char* getName() const final;

    DynamicBody* getBody() { return m_pBody; }
    const JumpBehaviour* getJumpBehaviour() const { return m_pJumpBehaviour; }

private:
    DynamicBody* m_pBody;
    const JumpBehaviour* m_pJumpBehaviour;
};

typedef std::shared_ptr<JumpEvent> JumpEventPtr;

#endif // JUMP_EVENT_H_
