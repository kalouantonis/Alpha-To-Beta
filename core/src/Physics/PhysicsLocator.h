#ifndef PHYSICS_LOCATOR_H
#define PHYSICS_LOCATOR_H

#include <Resources/Locator.h>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <SFML/System/Vector2.hpp>

#include <Physics/CollisionDispatcher.h>

class PhysicsLocator: public Locator<b2World> 
{
public:
	static sf::Vector2f PixelsPerMeter;

    static void provide(Ptr object);
	/**
	 * @brief Cretate physics World
	 * 
	 * @param object New physics World	
	 * @param ppp Pixels per meter
	 */
    static void provide(Ptr object, const sf::Vector2f& ppp);
	static void provide(const sf::Vector2f& gravity, const sf::Vector2f& ppp = sf::Vector2f(1, 1));

    static void remove();

	static b2Body* createStaticBody();
	static b2Body* createDynamicBody();

private:
    static std::unique_ptr<CollisionDispatcher> m_spCollisionDispatcher;
};

#endif // PHYSICS_LOCATOR_H
