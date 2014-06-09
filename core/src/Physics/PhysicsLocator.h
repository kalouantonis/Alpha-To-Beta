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

    /**
     * @brief Set physics world to that pointer to by ptr
     * 
     * @param object Physics world to use
     */
    static void provide(Ptr object);
	/**
	 * @brief Cretate physics World
	 * 
	 * @param object New physics World	
	 * @param ppp Pixels per meter
	 */
    static void provide(Ptr object, const sf::Vector2f& ppp);
    /**
     * @brief Create a new world using the given gravity and pixels per meter
     */
    static void provide(const sf::Vector2f& gravity,
                        const sf::Vector2f& ppp = sf::Vector2f(1, 1));
    /**
     * @brief Remove previous physics world
     */
    static void remove();

    /**
     * @brief Create new static body from world
     */
	static b2Body* createStaticBody();
    /**
     * @brief Create new dynamic body from world
     */
	static b2Body* createDynamicBody();

    static void convertToWorldCoords(sf::Vector2f& pos);
    static void convertToWorldCoords(float& x, float& y);

private:
    /**
     * Reference to collision dispatcher. Called when by world when collision events occur
     */
    static std::unique_ptr<CollisionDispatcher> m_spCollisionDispatcher;
};

#endif // PHYSICS_LOCATOR_H
