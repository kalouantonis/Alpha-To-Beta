#include <Components/DynamicBody.h>

#include <Physics/PhysicsLocator.h>

#include <glm/glm.hpp>
#include <tinyxml2.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

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
	: Physics(0.f, 0.f)
{
	body = PhysicsLocator::createDynamicBody();
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
        initializePolyVertices(polygonShape, 0.f, 0.f, m_dimensions.x, m_dimensions.y);

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
    // Override physics impl
    const tinyxml2::XMLElement* pChildElement = pElement->FirstChildElement("Dimensions");

    float xOffset = 0.f, yOffset = 0.f;

    if(pChildElement == NULL)
    {
        setDimensions(0.f, 0.f);
    }
    else
    {

        pChildElement->QueryFloatAttribute("x", &xOffset);
        pChildElement->QueryFloatAttribute("y", &yOffset);
        pChildElement->QueryFloatAttribute("width", &m_dimensions.x);
        pChildElement->QueryFloatAttribute("height", &m_dimensions.y);

        m_halfWidth = m_dimensions.x / 2.f;
        m_halfHeight = m_dimensions.y / 2.f;
    }

    for(const tinyxml2::XMLElement* pChildElement = pElement->FirstChildElement("Fixture");
        pChildElement != NULL; pChildElement = pElement->NextSiblingElement("Fixture"))
    {
        // TODO: Change to loading dimensions using each fixure independently
        b2PolygonShape polyShape;
        initializePolyVertices(polyShape, xOffset, yOffset, m_dimensions.x, m_dimensions.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polyShape;
        // Set to defaults
        _setToDefaults(fixtureDef);

        const tinyxml2::XMLElement* childElement =
                pChildElement->FirstChildElement("Properties");

        if(childElement)
        {
            childElement->QueryFloatAttribute("density", &fixtureDef.density);
            childElement->QueryFloatAttribute("friction", &fixtureDef.friction);
            childElement->QueryFloatAttribute("res", &fixtureDef.restitution);
        }

        childElement = pChildElement->FirstChildElement("Sensor");

        if(childElement)
        {
            childElement->QueryBoolText(&fixtureDef.isSensor);
        }

        body->CreateFixture(&fixtureDef);
    }

    pChildElement = pElement->FirstChildElement("FixedRotation");

    if(pChildElement != NULL)
    {
        bool bFixedRotation = false;
        if(pChildElement->QueryBoolText(&bFixedRotation) == tinyxml2::XML_CAN_NOT_CONVERT_TEXT)
            CORE_ERROR("Invalid boolean value for FixedRotation");

        body->SetFixedRotation(bFixedRotation);
    }

    return true;
}

void DynamicBody::initializePolyVertices(b2PolygonShape &polyShape, float xOffset, float yOffset, float width, float height)
{
    float halfWidth = width / 2.f;
    float halfHeight = height / 2.f;

    b2Vec2 polyVertices[4];
    // Bottom left
    polyVertices[0] = b2Vec2(-halfWidth + xOffset, -halfHeight + yOffset);
    // Bottom right
    polyVertices[1] = b2Vec2(halfWidth, -halfHeight + yOffset);
    // Top Right
    polyVertices[2] = b2Vec2(halfWidth, halfHeight);
    // Top left
    polyVertices[3] = b2Vec2(-halfWidth + xOffset, halfHeight);

    polyShape.Set(polyVertices, 4);
}
