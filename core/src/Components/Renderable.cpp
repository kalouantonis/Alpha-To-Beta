#include <Components/Renderable.h>
#include <tinyxml2.h>

#include <Utils/Logger.h>
#include <Utils/String.h>

#include <Resources/ResourceDef.h>

#include <Physics/PhysicsLocator.h>

const char* Renderable::g_name = "Renderable";

Renderable::Renderable(int order, float width, float height)
    : m_textureRegion(nullptr)
    , order(order)
    // Invalid width and height because no texture was provided
    , width(width), height(height)
{
}

Renderable::Renderable(sf::TexturePtr pTexture, int order, float width, float height)
    // Dont delegate, causes delegation cycle due to ambiguity
    : m_textureRegion(pTexture)
    , order(order)
{

	if(width == 0.f && height == 0.f)
	{
		// Region width
		width = m_textureRegion.u2 - m_textureRegion.u1;
		// Region height
		height = m_textureRegion.v2 - m_textureRegion.v1;
	}
	else
	{
		this->width = width;
		this->height = height;
	}
}

Renderable::Renderable(TextureRegion& region, int order, float width, float height)
    : order(order)
{
	if(width == 0.f && height == 0.f)
	{
		setTextureRegion(region);
	}
	else
	{
		m_textureRegion = region;
		this->width = width;
		this->height = height;
	}
}

bool Renderable::load(const tinyxml2::XMLElement *pElement)
{
	pElement->QueryIntAttribute("order", &order);

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
		pElement->QueryFloatAttribute("width", &width);
		pElement->QueryFloatAttribute("height", &height);

        width = width != 0 ? width / PhysicsLocator::PixelsPerMeter.x : 0;
        height = height != 0 ? height / PhysicsLocator::PixelsPerMeter.y : 0;
	}

    m_textureRegion = tmpRegion;

    return true;
}
