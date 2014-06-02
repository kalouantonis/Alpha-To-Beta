/*
 * TextureRegion.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#include <Graphics/TextureRegion.h>

// Dereferencing, gonna need this
#include <SFML/Graphics/Texture.hpp>

#include <assert.h>

TextureRegion::TextureRegion()
{
	setTexture(nullptr);
}

TextureRegion::TextureRegion(sf::TexturePtr pTexture)
{
	// Delegate to assignment op for texture,
	// discard return type as it acts on this
	//operator=(pTexture);
	setTexture(pTexture);
}

void TextureRegion::setTexture(sf::TexturePtr pTexture)
{
	// Store texture pointer
	m_pTexture = pTexture;

	// Get defined texture size
	sf::Vector2u texSize;

	if(pTexture)
	{
		texSize = pTexture->getSize();
	}
	else
	{
        // Invalidate, will not be drawn
        texSize = sf::Vector2u(0, 0);
	}

	u1 = v1 = 0;
	u2 = (float) texSize.x;
	v2 = (float) texSize.y;
}

TextureRegion::TextureRegion(sf::TexturePtr pTexture,
                             float x, float y, float width, float height)
	: m_pTexture(pTexture)
{
    u1 = x;
    v1 = y;
    u2 = u1 + width ;
    v2 = v1 + height;
}


