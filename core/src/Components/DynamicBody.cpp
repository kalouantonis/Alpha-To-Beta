#include <Components/DynamicBody.h>

#include <Physics/PhysicsLocator.h>

#include <glm/glm.hpp>
#include <tinyxml2.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <Utils/Logger.h>

const char* DynamicBody::g_name = "DynamicBody";

/**
 * @brief Set fixture variables to default values
 * @param fixtureDef
 */
void _setToDefaults(b2FixtureDef& fixtureDef)
{
        fixtureDef.density = 0.5f;
        fixtureDef.restitution = 0.2f;
        fixtureDef.friction = 0.4f;
}

DynamicBody::DynamicBody()
	: DynamicBody(0.f, 0.f)
{
}

DynamicBody::DynamicBody(float width, float height)
	: Physics(width, height)
{
    body = PhysicsLocator::createDynamicBody();
}

DynamicBody::DynamicBody(float x, float y, float width, float height)
    : Physics(width, height)
{
	// pre-initialize
	initialize(x, y);
}

DynamicBody::~DynamicBody()
{

}

void DynamicBody::initialize(float x, float y, float rotation)
{
	if(!isInitialized() && body == nullptr)
	{
		body = PhysicsLocator::createDynamicBody();
	}

	body->SetTransform(
		b2Vec2(x + m_halfWidth, y + m_halfHeight), 
		glm::radians(rotation)
	);

	// No fixtures
	if(body->GetFixtureList() == NULL)
	{
		// Create polygon shape by default
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(m_halfWidth, m_halfHeight);

        b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygonShape;
        // Use default values
        _setToDefaults(fixtureDef);

		// Create fixture and attach it to the body
		body->CreateFixture(&fixtureDef);
	}

	m_bInitialized = true;
}

bool DynamicBody::load(const tinyxml2::XMLElement* pElement)
{
    if(!Physics::load(pElement))
        return false;

    for(const tinyxml2::XMLElement* pChildElement = pElement->FirstChildElement("Fixture");
        pChildElement != NULL; pChildElement = pElement->NextSiblingElement("Fixture"))
    {
        // TODO: Change to loading dimensions using each fixure independently
        b2PolygonShape polyShape;
        polyShape.SetAsBox(m_halfWidth, m_halfHeight);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polyShape;
        // Set to defaults
        _setToDefaults(fixtureDef);

        const tinyxml2::XMLElement* propertyElement =
                pChildElement->FirstChildElement("Properties");

        if(propertyElement)
        {
            propertyElement->QueryFloatAttribute("density", &fixtureDef.density);
            propertyElement->QueryFloatAttribute("friction", &fixtureDef.friction);
            propertyElement->QueryFloatAttribute("res", &fixtureDef.restitution);
        }

        body->CreateFixture(&fixtureDef);
    }

    return true;
}
