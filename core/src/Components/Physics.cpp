#include <Components/Physics.h>
#include <Utils/Logger.h>

#include <tinyxml2.h>

const char* Physics::g_name = "Physics";

Physics::Physics(float mass)
	: bounds(0.f, 0.f, 0.f, 0.f)
	, mass(mass)
{

}

Physics::Physics(float x, float y, float width, float height, float mass)
	: bounds(x, y, width, height)
	, mass(mass)
{

}
