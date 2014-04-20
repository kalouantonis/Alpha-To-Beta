#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Components/ParsedComponent.h>
#include <SFML/System/Vector2.hpp>

class Transform: public ParsedComponent
{
public:
    Transform(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f);

    /**
     * @brief Load component from XML definition
     * 
     * @param element XML Element to load from
     * @return true if loading succeeded
     */
    virtual bool load(const tinyxml2::XMLElement *pElement) override;

    static const char* g_name;
    virtual const char* getName() const override { return g_name; }

    sf::Vector2f position;
    sf::Vector2f bounds;
    sf::Vector2f origin;
    sf::Vector2f scale;

    float rotation;
};

typedef std::shared_ptr<Transform> TransformPtr;

#endif // TRANSFORM_H
