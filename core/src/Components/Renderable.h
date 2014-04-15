#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <Components/ParsedComponent.h>
#include <SFMLPtrDef.h>
#include <Graphics/TextureRegion.h>

class Renderable: public ParsedComponent
{
public:
    /**
     * @brief Will create an empty renderable with a null texture
     */
    Renderable();
    explicit Renderable(TextureRegion& textureRegion);
    /**
     * @brief Renderable
     * @param texture
     */
    explicit Renderable(sf::TexturePtr texture);

    virtual bool load(const tinyxml2::XMLElement *pElement) override;

    static const char* g_name;
    virtual const char* getName() const override { return g_name; }

    // Constant, texture data can not be modified
    // Note: May change in the future if mods are needed
    TextureRegion textureRegion;
    // Draw order
    int order;
};

typedef std::shared_ptr<Renderable> RenderablePtr;

#endif // RENDERABLE_H
