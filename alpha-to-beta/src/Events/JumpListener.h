#ifndef JUMP_LISTENER_H_
#define JUMP_LISTENER_H_

#include <memory>

#include <Events/EventManager.h>

//fwd defs
//class IEventData;
//typedef std::shared_ptr<IEventData> EventDataPtr;

//struct JumpProperties
//{
//    const JumpBehaviourPtr jumpBehaviour;
//    JumpState jumpState;
//};

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
