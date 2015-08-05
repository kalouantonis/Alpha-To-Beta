#ifndef COLLISION_DISPATCHER_H_
#define COLLISION_DISPATCHER_H_

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class CollisionDispatcher: public b2ContactListener
{
public:
    /**
     * @brief Called when collision begins
     * 
     * @param contact box2d contact of collision
     */
    virtual void BeginContact(b2Contact* contact) final;
    /**
     * @brief Called when collision ends
     * 
     * @param contact box2d contact of collision
     */
    virtual void EndContact(b2Contact* contact) final;
};

#endif // COLLISION_DISPATCHER_H_
