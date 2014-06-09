#include <Physics/PhysicsLocator.h>

sf::Vector2f PhysicsLocator::PixelsPerMeter(1.f, 1.f);
std::unique_ptr<CollisionDispatcher> PhysicsLocator::m_spCollisionDispatcher = nullptr;

void PhysicsLocator::provide(Ptr object, const sf::Vector2f& ppp)
{
    PhysicsLocator::provide(object);
	PixelsPerMeter = ppp;
}

void PhysicsLocator::provide(const sf::Vector2f& gravity, const sf::Vector2f& ppp)
{
    PhysicsLocator::provide(Ptr(new b2World(b2Vec2(gravity.x, gravity.y))), ppp);
}

void PhysicsLocator::provide(Locator::Ptr object)
{
    Locator<b2World>::provide(object);

    m_spCollisionDispatcher.reset(
         new CollisionDispatcher()
    );

    getObject()->SetContactListener(m_spCollisionDispatcher.get());
}

void PhysicsLocator::remove()
{
    // Remove dispatcher from world
    getObject()->SetContactListener(NULL);
    m_spCollisionDispatcher = nullptr;

    Locator<b2World>::remove();
}

b2Body* PhysicsLocator::createStaticBody()
{
    // Separate to avoid the whole temporary object warning thing
	static b2BodyDef bodyDef;

	return getObject()->CreateBody(&bodyDef);
}

b2Body* PhysicsLocator::createDynamicBody()
{
	static b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_dynamicBody;

	return getObject()->CreateBody(&bodyDef);
}

void PhysicsLocator::convertToWorldCoords(sf::Vector2f& pos)
{
    convertToWorldCoords(pos.x, pos.y);
}

void PhysicsLocator::convertToWorldCoords(float& x, float& y)
{
    x /= PhysicsLocator::PixelsPerMeter.x;
    y /= PhysicsLocator::PixelsPerMeter.y;
}
