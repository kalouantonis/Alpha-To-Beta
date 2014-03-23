#ifndef RESOURCE_HOLDER_DEF_H
#define RESOURCE_HOLDER_DEF_H

#include <Resources/SharedResourceHolder.h>
#include <SFML/Graphics/Texture.hpp>

typedef SharedResourceHolder<std::string, sf::Texture> TextureHolder;

#endif // RESOURCE_HOLDER_DEF_H