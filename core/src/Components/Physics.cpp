#include <Components/Physics.h>
#include <Utils/Logger.h>

#include <tinyxml2.h>

const char* Physics::g_name = "Physics";

Physics::Physics(const sf::Vector2f& velocity, const sf::Vector2f& acceleration, float mass)
	: velocity(velocity)
	, acceleration(acceleration)
	, mass(mass)
{
}

bool Physics::load(const tinyxml2::XMLElement *pElement)
{
	const tinyxml2::XMLElement* childElement = pElement->FirstChildElement("Velocity");

	if(!childElement)
	{
		CORE_WARNING("No Velocity element declared in Physics component");
		return false;
	}

	childElement->QueryFloatAttribute("x", &velocity.x);
	childElement->QueryFloatAttribute("y", &velocity.y);

	childElement = pElement->FirstChildElement("Acceleration");

	if(childElement)
	{
		childElement->QueryFloatAttribute("x", &acceleration.x);
		childElement->QueryFloatAttribute("y", &acceleration.y);
	}

	childElement = pElement->FirstChildElement("Mass");

	if(childElement)
	{
		childElement->QueryFloatText(&mass);
	}

	return true;	
}

