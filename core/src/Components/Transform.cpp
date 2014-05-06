#include <Components/Transform.h>
#include <tinyxml2.h>

#include <Utils/Logger.h>

const char* Transform::g_name = "Transform";

Transform::Transform(float x, float y)
    : position(x, y)
    , origin(0.f, 0.f)
    , scale(1.f, 1.f)
    , rotation(0.f)
{
	// Validate origin
	//origin.x = (width != 0) ? width : 0;
	//origin.y = (height != 0) ? height : 0;
}

bool Transform::load(const tinyxml2::XMLElement *pElement)
{
	pElement->QueryFloatAttribute("x", &position.x);
	pElement->QueryFloatAttribute("y", &position.y);

	// pElement->QueryFloatAttribute("width", &bounds.x);
	// pElement->QueryFloatAttribute("height", &bounds.y);

	// Scale element, not required
	const tinyxml2::XMLElement* childElement = pElement->FirstChildElement("Scale");

	if(childElement)
	{
		pElement->QueryFloatAttribute("x", &scale.x);
		pElement->QueryFloatAttribute("y", &scale.y);
	}

	// Rotation element, not required
	childElement = pElement->FirstChildElement("Rotation");

	if(childElement)
	{
		childElement->QueryFloatAttribute("angle", &rotation);
	}

	return true;
}
