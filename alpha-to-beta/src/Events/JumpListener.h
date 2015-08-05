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

typedef std::shared_ptr<JumpListener> JumpListenerPtr;
typedef std::unique_ptr<JumpListener> UJumpListenerPtr;

#endif // JUMP_LISTENER_H_
