#include <Components/StaticBody.h>
#include <Physics/PhysicsLocator.h>

#include <glm/glm.hpp>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

const char* StaticBody::g_name = "StaticBody";

StaticBody::StaticBody()
	: Physics()
{
}

StaticBody::StaticBody(float width, float height)
	: Physics(width, height)
{
}

StaticBody::StaticBody(float x, float y, float width, float height, float rotation)
	: Physics(width, height)
{
	initialize(x, y, glm::radians(rotation));
}

void StaticBody::initialize(float x, float y, float rotation)
{
	body = PhysicsLocator::createStaticBody();
	body->SetTransform(
		b2Vec2(x + m_halfWidth, y + m_halfHeight), 
		glm::radians(rotation)
	);

	// use polygons only for now
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_halfWidth, m_halfHeight);

	body->CreateFixture(&polygonShape, 0.f);

	m_bInitialized = true;
}

