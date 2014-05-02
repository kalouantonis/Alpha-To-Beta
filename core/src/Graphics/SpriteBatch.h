#ifndef SFSPRITEBATCH_H
#define SFSPRITEBATCH_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFMLPtrDef.h>

#include <memory>

class TextureRegion;


class SpriteBatch
{
public:
    SpriteBatch(sf::RenderTargetPtr renderTarget, int capacity = 2000);
    ~SpriteBatch();

    /**
     * @brief Begin sprite batch rendering. TODO: May lock renderer
     */
    void begin();
    void end();

    // TODO: Check if I should use references of pointers
    // Also, fix it, because it doesnt work
    //void setShader(const sf::Shader* shader);

    void draw(sf::ConstTexturePtr pTexture, const sf::Vector2f& position,
        const sf::Vector2f& bounds);
    /**
     * @brief Draw a texture
     *
     * @param texture The texture needing drawing
     * @param x
     * @param y
     */
    void draw(sf::ConstTexturePtr pTexture, float x, float y);
    void draw(sf::ConstTexturePtr pTexture, float x, float y,
              float width, float height);
    void draw(sf::ConstTexturePtr pTexture, float x, float y, 
        float width, float height, float rotation);

    void draw(const TextureRegion& region, float x, float y,
              float width, float height);

    sf::RenderTargetPtr getRenderTarget() const { return m_pRenderTarget; }

private:
    void flush();
    void switchTexture(const sf::Texture* const pTexture);
    // Check the current state of the sprite batch.
    // Is in charge of swithing textures or flushing the buffer
    // if required
    void checkBatchState(const sf::Texture* const pTexture);

    /**
     * @brief Request next available quad from vertex buffer
     *
     * Allows modification of values
     *
     * @return A vertex
     */
    sf::Vertex* getNextQuad();

    sf::RenderTargetPtr m_pRenderTarget;
    sf::RenderStates m_states;
    // Vertex array
    sf::VertexArray m_vertices;

    unsigned int m_numSprites;
    unsigned int m_maxSprites;

    bool m_bDrawing;
};

typedef std::shared_ptr<SpriteBatch> SpriteBatchPtr;

#endif // SFSPRITEBATCH_H
