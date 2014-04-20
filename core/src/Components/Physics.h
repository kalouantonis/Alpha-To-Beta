#ifndef PHYSICS_H
#define PHYSICS_H

#include <Components/ParsedComponent.h>
#include <SFML/System/Vector2.hpp>

// #include <Systems/PhysicsSystem.h>

const float STATIC_BODY_MASS = 0.f;

class Physics: public ParsedComponent
{
	// friend class PhysicsSystem;

public:

	Physics(const sf::Vector2f& velocity = sf::Vector2f(0, 0), 
		const sf::Vector2f& acceleration = sf::Vector2f(0, 0), 
		float mass = STATIC_BODY_MASS);

	virtual bool load(const tinyxml2::XMLElement* pElement) override;

	static const char* g_name;
	virtual const char* getName() const override { return g_name; }

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	/**
	 * If mass is 0, it will be a static object
	 */
	float mass;

private:
};

typedef std::shared_ptr<Physics> PhysicsPtr;

#endif // PHYSICS_H
