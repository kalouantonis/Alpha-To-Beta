#include <Systems/PhysicsSystem.h>

#include <Utils/Logger.h>

// #include <chipmunk/chipmunk.h>

PhysicsSystem::PhysicsSystem(const sf::Vector2f& gravity)
{
	// Initialize physics system
	CORE_DEBUG("Creating physics space...");
	// Physics::m_spSpace = cpSpaceNew();
	// Set gravity
	CORE_DEBUG(
		"Setting physics gravity. X: " + 
		std::to_string(gravity.x) + " Y: " + 
		std::to_string(gravity.y)
	);
	// cpVect cpGravity = cpv(gravity.x, gravity.y);
	// cpSpaceSetGravity(Physics::m_spSpace, cpGravity);

	// Enable segment collisions... maybe?
	// cpEnableSegmentToSegmentCollisions();

	// Store localized reference
	// m_space = Physics::m_spSpace;
}

PhysicsSystem::~PhysicsSystem()
{
	// Free space
	// cpSpaceFree(Physics::m_spSpace);
	// Set to NULL in physics comps
	// Physics::m_spSpace = NULL;
	// Nullify here, for safety
	// m_space = NULL;
}


void PhysicsSystem::initialize()
{
}

void PhysicsSystem::begin()
{
	// Step physics
	// cpSpaceStep(m_space, world->getDelta());
}

void PhysicsSystem::processEntity(artemis::Entity &e)
{
	Transform* transform = m_transformMapper.get(e);
	DynamicBody* dynamicBody = m_physicsMapper.get(e);

	// Update transform position according to physics
	// transform->position = dynamicBody->getPosition();
}