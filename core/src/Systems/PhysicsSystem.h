#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include <Components/Transform.h>
#include <Components/DynamicBody.h>

class PhysicsSystem: public artemis::EntityProcessingSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	virtual void initialize() override;

	virtual void processEntity(artemis::Entity& e) final;

private:
	virtual void added(artemis::Entity& e) final;

	artemis::ComponentMapper<Transform> m_transformMapper;
};

#endif // PHYSICS_SYSTEM_H