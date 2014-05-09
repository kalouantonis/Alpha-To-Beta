#include <Components/Physics.h>
#include <Utils/Logger.h>

#include <tinyxml2.h>

#include <glm/glm.hpp>
#include <Box2D/Dynamics/b2Body.h>

#include <Physics/PhysicsLocator.h>

// const char* Physics::g_name = "Physics";

Physics::Physics()
	: body(nullptr)
	, m_dimensions(0.f, 0.f)
	, m_halfWidth(0.f)
	, m_halfHeight(0.f)
    , m_bInitialized(false)
{

}

Physics::Physics(float width, float height)
	: body(nullptr)
	, m_dimensions(width, height)
	, m_halfWidth(width / 2.f)
	, m_halfHeight(height / 2.f)
    , m_bInitialized(false)
{

}

Physics::~Physics()
{
	if(body)
	{
        PhysicsLocator::getObject()->DestroyBody(body);
        body = nullptr;
	}
}

void Physics::setDimensions(float width, float height)
{
	m_dimensions.x = width;
	m_dimensions.y = height;

	// set half height
    m_halfWidth = width / 2.f;
    m_halfHeight = height / 2.f;
}

bool Physics::load(const tinyxml2::XMLElement* pElement) 
{
	const tinyxml2::XMLElement* childElement = pElement->FirstChildElement("Dimensions");

	if(childElement != NULL)
	{
		// Need to load separetally, due to the use of referencing
		childElement->QueryFloatAttribute("width", &m_dimensions.x);
		childElement->QueryFloatAttribute("height", &m_dimensions.y);

		m_halfWidth = m_dimensions.x / 2.f;
		m_halfHeight = m_dimensions.y / 2.f;
	}

	return true;
}

sf::Vector2f Physics::getPosition() 
{
    assert(body != nullptr);

	return sf::Vector2f(
		// This should be center of mass, so we are trying to
		// convert to invert cartesian coordinates
		body->GetPosition().x - m_halfWidth, 
		body->GetPosition().y - m_halfHeight
	);
}

sf::Vector2f Physics::getOrigin()
{
	return sf::Vector2f(m_halfWidth, m_halfHeight);
}

float Physics::getRotation()
{
	return glm::degrees(body->GetAngle());
}
