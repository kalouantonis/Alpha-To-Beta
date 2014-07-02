#ifndef _IRENDERABLE_H_
#define _IRENDERABLE_H_

#include <Components/ParsedComponent.h>

class TextureRegion;

class IRenderable: public ParsedComponent
{
public:
	IRenderable(int order, float width = 0.f, float height = 0.f)
		: m_drawOrder(order)
		, m_width(width)
		, m_height(height)
	{
	}

	virtual ~IRenderable() {}

	float getWidth() const { return m_width; }
	float getHeight() const { return m_height; }
	int getDrawOrder() const { return m_drawOrder; }
	virtual const TextureRegion& getTextureRegion() const = 0;

	void setWidth(float w) { m_width = w; }
	void setHeight(float h) { m_height = h; }
	void setDrawOrder(int order) { m_drawOrder = order; }

protected:
	int m_drawOrder;
	float m_width, m_height;
};

#endif // _IRENDERABLE_H_
