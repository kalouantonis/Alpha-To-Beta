#ifndef RENDERABLE_H
#define RENDERABLE_H
// TODO: May need to change entity.h to separate components in to different headers
#include <entityx/Entity.h>
#include <Resources/ResourceHolderDef.h>
#include <SFMLPtrDef.h>

class Renderable: public entityx::Component<Renderable>
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

protected:
    TextureHolder& textureHolder() const { return m_sTextureHolder; }

private:
    /**
     * Static resource holder, used by this class and all inheritors
     */
    static TextureHolder m_sTextureHolder;
};

typedef std::shared_ptr<Renderable> RenderablePtr;

#endif // RENDERABLE_H
