#include <Components/Renderable.h>
#include <tinyxml2.h>

#include <Utils/Logger.h>
#include <Utils/String.h>

#include <Resources/ResourceDef.h>

// String trimming
#include <boost/algorithm/string.hpp>

const char* Renderable::g_name = "Renderable";

Renderable::Renderable()
    : pTexture(nullptr)
    , order(0)
{

}

Renderable::Renderable(sf::TexturePtr texture)
    : pTexture(texture)
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

	std::string textureId = make_string(textureElement->Attribute("id"));

	if(textureId.empty())
		textureId = textureFile;

	bool smooth = false;
	textureElement->QueryBoolAttribute("smooth", &smooth);

	try
	{
		TextureLocator::getObject()->load(textureId, textureFile);
	}
	catch(std::runtime_error& ex)
	{
		CORE_ERROR(ex.what());
		return false;
	}

	this->pTexture = TextureLocator::getObject()->get(textureId);

	if(smooth)
		this->pTexture->setSmooth(true);

    return true;
}