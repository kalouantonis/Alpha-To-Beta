#ifndef STATIC_BODY_H
#define STATIC_BODY_H

#include <Components/Physics.h>

class StaticBody: public Physics
{
public:
	StaticBody();
	explicit StaticBody(float width, float height);
	/**
	 * @brief Create static body
	 * @details In this case, the object will be initialized
	 */
	explicit StaticBody(float x, float y, float width, float height, float rotation = 0.f);

	static const char* g_name;
	virtual const char* getName() const final { return g_name; }

	// virtual bool load(const tinyxml2::XMLElement* pElement) override {}
	virtual void initialize(float x, float y, float rotation = 0.f) final;
};


#endif // STATIC_BODY_H
