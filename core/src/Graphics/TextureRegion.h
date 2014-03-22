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
    TextureRegion(sf::ConstTexturePtr texture, float x, float y,
                  float width, float height);

	float u1, v1;
	float u2, v2;

    sf::ConstTexturePtr getTexture() const { return m_texture; }

private:
	// Not sure if i should use referencing or strongptr
    sf::ConstTexturePtr m_texture;
};

#endif /* TEXTUREREGION_H_ */
