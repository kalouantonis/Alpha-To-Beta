#ifndef DYNAMIC_BODY_H
#define DYNAMIC_BODY_H

#include <Components/Physics.h>
#include <SFML/System/Vector2.hpp>

class b2PolygonShape;

class DynamicBody: public Physics
{
public:
	DynamicBody();
	explicit DynamicBody(float width, float height);
	explicit DynamicBody(float x, float y, float width, float height);
     ~DynamicBody();

	static const char* g_name;
	virtual const char* getName() const final { return g_name; }

    /**
     * @brief Initialize component using position coordinates
     * @details Must be used to correctly add component to world
     * 
     * @param x X position
     * @param y Y position
     * @param rotation Rotation of sprite. Defaults to 0
     */
	virtual void initialize(float x, float y, float rotation = 0.f) final;
    /**
     * @brief Load component from xml element
     * @details initialize must be called after to set position
     */
	virtual bool load(const tinyxml2::XMLElement* pElement) final;

private:
    /**
     * @brief Initialize box2d polygon fixture
     * 
     * @param polyShape Shape reference
     * @param xOffset X offset from entity origin
     * @param yOffset Y offset from entity origin 
     * @param width Width of fixture
     * @param height Height of fixture
     */
    void initializePolyVertices(b2PolygonShape& polyShape,
                                float xOffset, float yOffset,
                                float width, float height);
};

#endif // DYNAMIC_BODY_H
