#include <Components/Transform.h>
#include <tinyxml2.h>

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
	return false;
}
