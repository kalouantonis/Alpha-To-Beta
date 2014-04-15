#include <Components/Renderable.h>
#include <tinyxml2.h>

#include <Utils/Logger.h>
#include <Utils/String.h>
#include <Utils/Helpers.h>

#include <Resources/ResourceDef.h>

// String trimming
#include <boost/algorithm/string.hpp>

const char* Renderable::g_name = "Renderable";

Renderable::Renderable()
    : textureRegion(nullptr)
    , order(0)
{

}

Renderable::Renderable(TextureRegion& region)
	: textureRegion(region)
{

}

Renderable::Renderable(sf::TexturePtr texture)
    : textureRegion(texture)
{
}

bool Renderable::load(const tinyxml2::XMLElement *pElement)
{
	pElement->QueryIntAttribute("order", &order);

	const tinyxml2::XMLElement* textureElement = pElement->FirstChildElement("Texture");

	if(!textureElement)
	{
		CORE_WARNING("No Texture element declared in Renderable component.");

		return false;
	}
	
	// Get file name
	std::string textureFile = make_string(textureElement->GetText());

	if(textureFile.empty())
	{
		CORE_WARNING("No texture file defined in Renderable Component");
		return false;
	}

	// Trim whitespace
	boost::algorithm::trim(textureFile);

	sf::TexturePtr pTexture = TextureLocator::getObject()->get(textureFile);

	if(!pTexture)
	{
		CORE_ERROR("Failed to get texture: " + textureFile);
		return false;
	}

	this->textureRegion.setTexture(pTexture);

    return true;
}
