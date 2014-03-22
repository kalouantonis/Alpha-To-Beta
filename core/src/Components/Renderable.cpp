#include <Components/Renderable.h>
#include <tinyxml2.h>

#include <Resources/SingletonTextureHolder.h>
#include <Utils/Logger.h>


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
	const tinyxml2::XMLElement* textureElement = pElement->FirstChildElement("Texture");

	if(!textureElement)
	{
		CORE_WARNING("No Texture element declared in Renderable component.");

		return false;
	}

	order = textureElement->QueryAttribute("order", &order);

	const tinyxml2::XMLElement* fileElem = textureElement->FirstChildElement("File");

	if(!fileElem)
	{
		CORE_WARNING("No File element declared in Renderable component.");

		return false;
	}

	// Get file name
	const char* textureFile = fileElem->GetText();

	const tinyxml2::XMLElement* textureIdElem = textureElement->FirstChildElement("ID");

	const char* textureId = nullptr;

	if(textureIdElem)
	{
		textureId = textureIdElem->GetText();
	}
	else
	{
		textureId = textureFile;
	}

	SingletonTextureHolder::instance().load(textureId, textureFile);

	this->pTexture = SingletonTextureHolder::instance().get(textureId);

    return true;
}

