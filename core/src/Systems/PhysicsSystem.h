#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include <Components/Transform.h>
#include <Components/DynamicBody.h>

class PhysicsSystem: public artemis::EntityProcessingSystem
{
public:
	PhysicsSystem(const sf::Vector2f& gravity);
	~PhysicsSystem();

	virtual void initialize() override;
	virtual void processEntity(artemis::Entity& e) final;

private:
	virtual void begin() final;

	// cpSpace* m_space;

	artemis::ComponentMapper<Transform> m_transformMapper;
	// Only apply physics operations on dynamic bodies
	artemis::ComponentMapper<DynamicBody> m_physicsMapper;
};

#endif // PHYSICS_SYSTEM_H