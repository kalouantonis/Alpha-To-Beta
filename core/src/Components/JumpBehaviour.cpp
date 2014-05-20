#include <Components/JumpBehaviour.h>

#include <tinyxml2.h>

#include <Utils/Logger.h>

const char* JumpBehaviour::g_name = "JumpBehaviour";

JumpBehaviour::JumpBehaviour(float yImpulse)
	: impulse(0.f, yImpulse)
{
}

JumpBehaviour::~JumpBehaviour()
{
}

bool JumpBehaviour::load(const tinyxml2::XMLElement *pElement)
{
    const tinyxml2::XMLElement* pChildElement =
            pElement->FirstChildElement("Impulse");

	if(!pChildElement)
	{
		CORE_ERROR("No impulse element defined for JumpBehaviour");
		return false;
	}

	// No X value, always use Y for jumping
	pChildElement->QueryFloatText(&impulse.y);

	return true;
}
