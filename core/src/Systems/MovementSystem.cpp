#include <Systems/MovementSystem.h>

MovementSystem::MovementSystem()
{
	addComponentType<Transform>();
	addComponentType<Physics>();
}

void MovementSystem::initialize()
{
	m_transformMapper.init(*world);
	m_physicsMapper.init(*world);
}

void MovementSystem::processEntity(artemis::Entity& e)
{
	Transform* pTransform = m_transformMapper.get(e);
	Physics* pPhysics = m_physicsMapper.get(e);

	// Get delta time
	float dt = world->getDelta();

	// Update velocity
	if(pPhysics->mass != 0)
	{
		pPhysics->velocity += (pPhysics->mass != 0)
			? ((pPhysics->acceleration * pPhysics->mass) * dt)
			: (pPhysics->acceleration * dt);
	}

	// Update position
	pTransform->position += pPhysics->velocity * dt;
}