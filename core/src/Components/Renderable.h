#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFMLPtrDef.h>
#include <Components/ParsedComponent.h>

class Renderable: public ParsedComponent<Renderable>
{
public:
    /**
     * @brief Will create an empty renderable with a null texture
     */
    Renderable();
    /**
     * @brief Renderable
     * @param texture
     */
    explicit Renderable(sf::TexturePtr texture);

    virtual bool load(const tinyxml2::XMLElement *pElement) override;

    // Constant, texture data can not be modified
    // Note: May change in the future if mods are needed
    sf::TexturePtr pTexture;
    // Draw order
    int order;
};

typedef std::shared_ptr<Renderable> RenderablePtr;

#endif // RENDERABLE_H
