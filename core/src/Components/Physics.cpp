#include <Components/Physics.h>

Physics::Physics(float xVel, float yVel, 
		float xAccel, float yAccel, float mass)
	: velocity(xVel, yVel)
	, acceleration(xAccel, yAccel)
	, mass(mass)
{
}

bool Physics::load(const tinyxml2::XMLElement *pElement)
{
	return false;	
}

