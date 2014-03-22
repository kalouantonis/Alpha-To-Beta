#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <entityx/System.h>

class MovementSystem: public entityx::System<MovementSystem>
{
public:
	void update(entityx::ptr<entityx::EntityManager> es, 
		entityx::ptr<entityx::EventManager> event, float dt) override;
};

#endif // MOVEMENT_SYSTEM_H