#ifndef DYNAMIC_BODY_H
#define DYNAMIC_BODY_H

#include <Components/Physics.h>
#include <SFML/System/Vector2.hpp>

class DynamicBody: public Physics
{
public:
	DynamicBody();
	explicit DynamicBody(float width, float height);
	explicit DynamicBody(float x, float y, float width, float height);
     ~DynamicBody();

	static const char* g_name;
	virtual const char* getName() const final { return g_name; }

	virtual void initialize(float x, float y, float rotation = 0.f) final;
	virtual bool load(const tinyxml2::XMLElement* pElement) final;
};

#endif // DYNAMIC_BODY_H
