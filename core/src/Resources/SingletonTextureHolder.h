#ifndef SINGLETONTEXTUREHOLDER_H
#define SINGLETONTEXTUREHOLDER_H

#include <Resources/SingletonResourceHolder.h>
#include <SFML/Graphics/Texture.hpp>

typedef SingletonResouceHolder<std::string, sf::Texture> SingletonTextureHolder;


#endif // SINGLETONTEXTUREHOLDER_H
