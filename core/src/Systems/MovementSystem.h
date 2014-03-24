#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include <Components/Transform.h>
#include <Components/Physics.h>

class MovementSystem: public artemis::EntityProcessingSystem
{
public:
	MovementSystem();

	virtual void initialize() override;
	virtual void processEntity(artemis::Entity& e) override;

private:
	artemis::ComponentMapper<Transform> m_transformMapper;
	artemis::ComponentMapper<Physics> m_physicsMapper;
};

#endif // MOVEMENT_SYSTEM_H