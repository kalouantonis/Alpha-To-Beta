#include <Systems/PhysicsSystem.h>
#include <Components/StaticBody.h>
#include <Utils/Logger.h>

#include <Artemis/Entity.h>

#include <Box2D/Dynamics/b2Body.h>

PhysicsSystem::PhysicsSystem()
{
    addComponentType<Transform>();
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::initialize()
{
	m_transformMapper.init(*world);
	m_physicsMapper.init(*world);
}

void PhysicsSystem::added(artemis::Entity& e)
{
    // Static cast is safe, as the constructor ensures that
    // we only receive entities that contain a Transform component
	Transform* transformComp = static_cast<Transform*>(
		e.getComponent<Transform>()
	);

	Physics* body = dynamic_cast<Physics*>(
		e.getComponent<StaticBody>()
	);

	// No static body
    if(body == nullptr)
	{
		// Try and receive dynamic body
		body = dynamic_cast<Physics*>(
			e.getComponent<DynamicBody>()
		);
	}

    if((body != nullptr && !body->isInitialized()))
	{
		body->initialize(
			transformComp->position.x, 
			transformComp->position.y,
			transformComp->rotation
		);

        // Set transform origiin
		transformComp->origin = body->getOrigin();

        // Set user data of body to the entity
        body->body->SetUserData(&e);
	}
}

void PhysicsSystem::processEntity(artemis::Entity &e)
{
	Transform* transform = m_transformMapper.get(e);
	DynamicBody* dynamicBody = m_physicsMapper.get(e);
	
    if(dynamicBody != NULL)
	{
		transform->position = dynamicBody->getPosition();
		transform->rotation = dynamicBody->getRotation();
	}
}
