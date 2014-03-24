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
	Transform* transform = m_transformMapper.get(e);
	Physics* physics = m_physicsMapper.get(e);

	// Get delta time
	float dt = world->getDelta();

	// Update velocity
	if(physics->mass != 0)
		physics->velocity += (physics->acceleration * physics->mass) * dt;

	// Update position
	transform->position += physics->velocity * dt;
}

// void MovementSystem::update(entityx::ptr<entityx::EntityManager> es, 
// 	entityx::ptr<entityx::EventManager> event, float dt)
// {
// 	for(auto entity : es->entities_with_components<Transform, Physics>())
// 	{
// 		// Get components
// 		TransformPtr transform = entity.component<Transform>();
// 		PhysicsPtr physics = entity.component<Physics>();

// 		// Update velocity
// 		if(physics->mass != 0)
// 			physics->velocity += (physics->acceleration * physics->mass) * dt;

// 		// Update position
// 		transform->position += physics->velocity * dt;
// 	}
// }