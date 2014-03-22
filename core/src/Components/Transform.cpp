#include <Components/Transform.h>
#include <tinyxml2.h>

#include <Utils/Logger.h>

Transform::Transform(float x, float y, float width, float height)
    : position(x, y)
    , bounds(width, height)
    , scale(1.f, 1.f)
    , rotation(0.f)
{
	// Validate origin
	origin.x = (width != 0) ? width : 0;
	origin.y = (height != 0) ? height : 0;
}

bool Transform::load(const tinyxml2::XMLElement *pElement)
{
	// Get position element
	const tinyxml2::XMLElement* transformElem = pElement->FirstChildElement("Transform");

	if(!transformElem)
	{
		CORE_WARNING("No transform element for Transform component.");
		return false;
	}

	position.x = transformElem->QueryAttribute("x", &position.x);
	position.y = transformElem->QueryAttribute("y", &position.y);

	bounds.x = transformElem->QueryAttribute("width", &bounds.x);
	bounds.y = transformElem->QueryAttribute("height", &bounds.y);

	// Scale element, not required
	const tinyxml2::XMLElement* scaleElem = pElement->FirstChildElement("Scale");

	if(scaleElem)
	{
		scale.x = transformElem->QueryAttribute("x", &scale.x);
		scale.y = transformElem->QueryAttribute("y", &scale.y);
	}

	// Rotation element, not required
	const tinyxml2::XMLElement* rotationElem = pElement->FirstChildElement("Rotation");

	if(rotationElem)
	{
		rotation = rotationElem->QueryAttribute("angle", &rotation);
	}

	return true;
}
