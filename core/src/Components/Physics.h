#ifndef PHYSICS_H
#define PHYSICS_H

#include <Components/ParsedComponent.h>

#include <SFML/Graphics/Rect.hpp>

class Physics: public ParsedComponent
{
	// Allow physics system to access hidden properties
	friend class PhysicsSystem;

public:
	Physics(float mass = 0.f);
	explicit Physics(float x, float y, float width, float height, float mass = 0.f);

	static const char* g_name;
	virtual const char* getName() const override { return g_name; }

	sf::FloatRect bounds;
	float mass;
};

typedef std::shared_ptr<Physics> PhysicsPtr;

#endif // PHYSICS_H
