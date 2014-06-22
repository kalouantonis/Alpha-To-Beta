#include <Components/JumpBehaviour.h>

#include <tinyxml2.h>

#include <Utils/Logger.h>

const char* JumpBehaviour::g_name = "JumpBehaviour";

JumpBehaviour::JumpBehaviour(float yImpulse, unsigned int maxJumps)
	: impulse(0.f, yImpulse)
    , m_numJumps(0)
    , m_maxJumps(maxJumps)
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

    pChildElement = pElement->FirstChildElement("MaxJumps");

    if(pChildElement)
    {
        pChildElement->QueryUnsignedText(&m_maxJumps);
    }

	return true;
}
