/*
 * TextureRegion.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#include <Graphics/TextureRegion.h>

TextureRegion::TextureRegion(sf::ConstTexturePtr texture,
                             float x, float y, float width, float height)
	: m_texture(texture)
{
    u1 = x;
    v1 = y;
    u2 = u1 + width ;
    v2 = v1 + height;
}


