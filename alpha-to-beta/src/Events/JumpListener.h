#ifndef JUMP_LISTENER_H_
#define JUMP_LISTENER_H_

#include <memory>

#include <Events/EventManager.h>

//fwd defs
//class IEventData;
//typedef std::shared_ptr<IEventData> EventDataPtr;

class JumpListener
{
public:
    JumpListener();
    ~JumpListener();

private:
    void receive(EventDataPtr pEvent);
};

#endif // JUMP_LISTENER_H_
