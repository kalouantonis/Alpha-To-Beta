/*
 * TextureRegion.h
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#ifndef TEXTUREREGION_H_
#define TEXTUREREGION_H_

#include <SFMLPtrDef.h>

class TextureRegion
{
public:
    TextureRegion();
	explicit TextureRegion(sf::TexturePtr pTexture);
    explicit TextureRegion(sf::TexturePtr pTexture, float x, float y,
                  float width, float height);

    // Overload assignment op for textures
    // Allows backwards compatibility with plain texture pointers
    // TextureRegion& operator=(sf::TexturePtr pTexture);

	float u1, v1;
	float u2, v2;

    sf::ConstTexturePtr getTexture() const { return m_pTexture; }
    void setTexture(sf::TexturePtr pTexture);

    float getWidth() const { return u2 - u1; }
    float getHeight() const { return v2 - v1; }

private:
	// TODO: Type and find a way to keep constants
    //sf::TexturePtr m_pTexture;
    sf::TexturePtr m_pTexture;
};

#endif /* TEXTUREREGION_H_ */
