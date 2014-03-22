#include <Components/Renderable.h>
#include <Resources/SingletonResourceHolder.h>


Renderable::Renderable()
    : pTexture(nullptr)
{

}

Renderable::Renderable(sf::ConstTexturePtr texture)
    : pTexture(texture)
{
}

bool Renderable::load(const tinyxml2::XMLElement *pElement)
{
    return false;
}

