#ifndef RESOURCEDEF_H
#define RESOURCEDEF_H

#include <Resources/SharedResourceHolder.h>
#include <Resources/Locator.h>
#include <SFML/Graphics/Texture.hpp>

typedef SharedResourceHolder<std::string, sf::Texture> TextureHolder;
typedef Locator<TextureHolder> TextureLocator;

#endif // RESOURCEDEF_H