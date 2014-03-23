#include <Systems/MovementSystem.h>

#include <Components/Transform.h>
#include <Components/Physics.h>


void MovementSystem::update(entityx::ptr<entityx::EntityManager> es, 
	entityx::ptr<entityx::EventManager> event, float dt)
{
	for(auto entity : es->entities_with_components<Transform, Physics>())
	{
		// Get components
		TransformPtr transform = entity.component<Transform>();
		PhysicsPtr physics = entity.component<Physics>();

		// Update velocity
		if(physics->mass != 0)
			physics->velocity += (physics->acceleration * physics->mass) * dt;

		// Update position
		transform->position += physics->velocity * dt;
	}
}