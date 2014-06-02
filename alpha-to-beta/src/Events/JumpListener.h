#ifndef JUMP_LISTENER_H_
#define JUMP_LISTENER_H_

#include <memory>

#include <Events/EventManager.h>

class JumpListener
{
public:
    JumpListener();
    ~JumpListener();

private:
    void receiveJumpEvt(EventDataPtr pEvent);
    void receiveBeginCollisionEvt(EventDataPtr pEvent);
};

#endif // JUMP_LISTENER_H_
