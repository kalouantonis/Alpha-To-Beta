#include <Systems/PhysicsSystem.h>

void PhysicsSystem::begin()
{
	// Step physics
}

void PhysicsSystem::processEntity(artemis::Entity &e)
{
	Transform* transform = m_transformMapper.get(e);
	Physics* physics = m_transformMapper.get(e);

	// Update transform position according to physics
	transform.position = physics.getPosition();
}