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
    Renderable(int order = 0, float width = 0.f, float height = 0.f);
    explicit Renderable(TextureRegion& textureRegion, int order = 0, float width = 0.f, float height = 0.f);
    /**
     * @brief Renderable
     * @param texture
     */
    explicit Renderable(sf::TexturePtr pTexture, int order = 0, float width = 0.f, float height = 0.f);

    virtual bool load(const tinyxml2::XMLElement *pElement) override;

    static const char* g_name;
    virtual const char* getName() const override { return g_name; }

    void setTextureRegion(const TextureRegion& textureRegion)
    {
        m_textureRegion = textureRegion;
        // Region width
        width = m_textureRegion.u2 - m_textureRegion.u1;
        // Region height
        height = m_textureRegion.v2 - m_textureRegion.v1;
    }

    const TextureRegion& getTextureRegion() const { return m_textureRegion; }
    /**
     * @brief non-const overload
     */
    TextureRegion& getTextureRegion() { return m_textureRegion; }

    // Draw order
    int order;
    float width, height;

private:
    TextureRegion m_textureRegion;
};

typedef std::shared_ptr<Renderable> RenderablePtr;

#endif // RENDERABLE_H
