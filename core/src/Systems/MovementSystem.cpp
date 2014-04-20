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

	float mass = pPhysics->mass;

	// Update velocity
	if(mass != 0.f)
	{
		pPhysics->velocity += (pPhysics->acceleration * mass) * dt;
	}

	// Update position
	pTransform->position += pPhysics->velocity * dt;
}