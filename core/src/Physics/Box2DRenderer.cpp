#include <Physics/Box2DRenderer.h>

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

const float Box2DRenderer::OUTLINE_THICKNESS = 0.02f;

Box2DRenderer::Box2DRenderer(sf::RenderTargetPtr pRenderTarget) 
	: m_pRenderTarget(pRenderTarget)
{

}	

sf::Color Box2DRenderer::b2SFColor(const b2Color& color, int alpha)
{
	return sf::Color(
		color.r * 255,
		color.g * 255,
		color.b * 255,
		alpha
	);
}

void Box2DRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
	sf::ConvexShape polygon(vertexCount);

	for(int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 vertex = vertices[i];
		polygon.setPoint(i, sf::Vector2f(vertex.x, vertex.y));
	}

	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(b2SFColor(color));
	polygon.setOutlineThickness(OUTLINE_THICKNESS);

	// Dont bother batching, we dont need the performance
	m_pRenderTarget->draw(polygon);
}

void Box2DRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);

	for(int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 vertex = vertices[i];
		polygon.setPoint(i, sf::Vector2f(vertex.x, vertex.y));
	}

	// Sort of transparent
	polygon.setFillColor(b2SFColor(color, 50));
	polygon.setOutlineColor(b2SFColor(color));
	polygon.setOutlineThickness(OUTLINE_THICKNESS);

	// Dont bother batching, we dont need the performance
	m_pRenderTarget->draw(polygon);
}

void Box2DRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape circle(radius);

	circle.setPosition(center.x - radius, center.y - radius);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(b2SFColor(color));
	circle.setOutlineThickness(OUTLINE_THICKNESS);

	m_pRenderTarget->draw(circle);
}

void Box2DRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius);

	circle.setPosition(center.x - radius, center.y - radius);
	circle.setFillColor(b2SFColor(color, 50));
	circle.setOutlineColor(b2SFColor(color));
	circle.setOutlineThickness(OUTLINE_THICKNESS);

	// Line of the circle that shows the angle
	DrawSegment(center, center + (radius * axis), color);

	m_pRenderTarget->draw(circle);
}

void Box2DRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) 
{
	sf::VertexArray line;

	line.append(sf::Vertex(sf::Vector2f(p1.x, p1.y), b2SFColor(color)));
	line.append(sf::Vertex(sf::Vector2f(p2.x, p2.y), b2SFColor(color)));
	// Draw as a line, obviously
	line.setPrimitiveType(sf::Lines);

	m_pRenderTarget->draw(line);
}

void Box2DRenderer::DrawTransform(const b2Transform& xf)
{
	float lineProportion = 0.4f;

	b2Vec2 point1 = xf.p;

	// Red X axis
	b2Vec2 point2 = point1 + (lineProportion * xf.q.GetXAxis());
	DrawSegment(point1, point2, b2Color(255, 0, 0));

	// Green Y axis
	point2 = point1 + (lineProportion * xf.q.GetYAxis());
	DrawSegment(point1, point2, b2Color(0, 255, 0));
}