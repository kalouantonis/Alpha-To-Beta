#include <Physics/PhysicsLocator.h>

sf::Vector2f PhysicsLocator::PixelsPerMeter(1.f, 1.f);

void PhysicsLocator::provide(Ptr object, const sf::Vector2f& ppp)
{
	Locator<b2World>::provide(object);
	PixelsPerMeter = ppp;
}

void PhysicsLocator::provide(const sf::Vector2f& gravity, const sf::Vector2f& ppp)
{
	PhysicsLocator::provide(Ptr(new b2World(b2Vec2(gravity.x, gravity.y))), ppp);
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
