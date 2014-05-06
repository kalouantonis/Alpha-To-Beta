#ifndef BOX2D_RENDERER_H
#define BOX2D_RENDERER_H

#include <Box2D/Common/b2Draw.h>

#include <SFMLPtrDef.h>
#include <SFML/Graphics/Color.hpp>

class Box2DRenderer: public b2Draw
{
public:
	Box2DRenderer(sf::RenderTargetPtr pRenderTarget);

	/// Draw a closed polygon provided in CCW order.
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf);

private:
		/**
	 * @brief Convert box2d color to sfml color
	 */
	sf::Color b2SFColor(const b2Color& color, int alpha = 255);

	sf::RenderTargetPtr m_pRenderTarget;

	static constexpr float OUTLINE_THICKNESS = 0.02f;
};

#endif // BOX2D_RENDERER_H
