#ifndef COLLISION_DISPATCHER_H_
#define COLLISION_DISPATCHER_H_

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class CollisionDispatcher: public b2ContactListener
{
public:
    virtual void BeginContact(b2Contact* contact) final;
    virtual void EndContact(b2Contact* contact) final;
};

#endif // COLLISION_DISPATCHER_H_
