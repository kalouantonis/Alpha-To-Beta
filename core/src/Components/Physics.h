#ifndef PHYSICS_H
#define PHYSICS_H

#include <Components/ParsedComponent.h>
#include <SFML/System/Vector2.hpp>

class Physics: public ParsedComponent
{
public:
	Physics(float xVel = 0.f, float yVel = 0.f, 
		float xAccel = 0.f, float yAccel = 0.f, 
		float mass = 0.f);

	virtual bool load(const tinyxml2::XMLElement* pElement) override;

	static const char* g_name;
	virtual const char* getName() const override { return g_name; }

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
};

typedef std::shared_ptr<Physics> PhysicsPtr;

#endif // PHYSICS_H
