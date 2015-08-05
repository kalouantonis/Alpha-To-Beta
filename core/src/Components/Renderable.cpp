#include <Components/Renderable.h>
#include <tinyxml2.h>

#include <Utils/Logger.h>
#include <Utils/String.h>

#include <Resources/ResourceDef.h>

#include <Physics/PhysicsLocator.h>

const char* Renderable::g_name = "Renderable";

Renderable::Renderable(int order, float width, float height)
	: IRenderable(order, width, height)
    , m_textureRegion(nullptr)
    // Invalid width and height because no texture was provided
{
}

Renderable::Renderable(sf::TexturePtr pTexture, int order, float width, float height)
    // Dont delegate, causes delegation cycle due to ambiguity
	: IRenderable(order)
    , m_textureRegion(pTexture)
{

	if(width == 0.f && height == 0.f)
	{
		// Region width
		setWidth(m_textureRegion.u2 - m_textureRegion.u1);
		// Region height
		setHeight(m_textureRegion.v2 - m_textureRegion.v1);
	}
	else
	{
		setWidth(width);
		setHeight(height);
	}
}

Renderable::Renderable(TextureRegion& region, int order, float width, float height)
	: IRenderable(order)
{
	if(width == 0.f && height == 0.f)
	{
		setTextureRegion(region);
	}
	else
	{
		m_textureRegion = region;
		setWidth(width);
		setHeight(height);
	}
}

bool Renderable::load(const tinyxml2::XMLElement *pElement)
{
	pElement->QueryIntAttribute("order", &m_drawOrder);

	const tinyxml2::XMLElement* childElement = pElement->FirstChildElement("Texture");

	if(!childElement)
	{
		CORE_WARNING("No Texture element declared in Renderable component.");

		return false;
	}

	// Get file name
	std::string textureFile = make_string(childElement->GetText());

	if(textureFile.empty())
	{
		CORE_WARNING("No texture file defined in Renderable Component");
		return false;
	}

	// Trim whitespace
	trim(textureFile);

	sf::TexturePtr pTexture = TextureLocator::getObject()->get(textureFile);

	if(!pTexture)
	{
		CORE_ERROR("Failed to get texture: " + textureFile);
		return false;
	}

	TextureRegion tmpRegion(pTexture);

	childElement = pElement->FirstChildElement("Dimensions");

	if(childElement)
	{
		pElement->QueryFloatAttribute("width", &m_width);
		pElement->QueryFloatAttribute("height", &m_height);

        setWidth(m_width != 0 ? m_width / PhysicsLocator::PixelsPerMeter.x : 0);
        setHeight(m_height != 0 ? m_height / PhysicsLocator::PixelsPerMeter.y : 0);
	}

    m_textureRegion = tmpRegion;

    return true;
}
