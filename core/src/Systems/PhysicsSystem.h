#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include <Components/Transform.h>
#include <Components/Physics.h>

class PhysicsSystem: public artemis::EntityProcessingSystem
{
public:
	PhysicsSystem();

	virtual void initialize() override;
	virtual void processEntity(artemis::Entity& e) final;

private:
	virtual void begin() final;

	artemis::ComponentMapper<Transform> m_transformMapper;
	artemis::ComponentMapper<Physics> m_physicsMapper;
};

#endif // PHYSICS_SYSTEM_H