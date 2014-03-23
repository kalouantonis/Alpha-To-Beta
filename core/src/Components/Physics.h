#ifndef PHYSICS_H
#define PHYSICS_H

#include <entityx/Entity.h>
#include <SFML/System/Vector2.hpp>

class Physics: public entityx::Component<Physics>
{
public:
	Physics(float xVel = 0.f, float yVel = 0.f, 
		float xAccel = 0.f, float yAccel = 0.f, 
		float mass = 1.f);

	virtual bool load(const tinyxml2::XMLElement* pElement) override;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
};

typedef std::shared_ptr<Physics> PhysicsPtr;

#endif // PHYSICS_H
