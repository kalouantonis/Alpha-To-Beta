#include <Graphics/SpriteBatch.h>
#include <Graphics/TextureRegion.h>
#include <Utils/Logger.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <assert.h>

const unsigned short VERTICES_IN_QUAD = 4;

SpriteBatch::SpriteBatch(sf::RenderTargetPtr renderTarget, int capacity)
    : m_pRenderTarget(renderTarget)
    , m_vertices(sf::Quads, capacity * VERTICES_IN_QUAD)
    , m_numSprites(0)
    , m_maxSprites(capacity)
    , m_bDrawing(false)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::begin()
{
    // Make sure end wasn't called before begin
    assert(!m_bDrawing && "Must call end before begin");

    m_bDrawing = true;
}

void SpriteBatch::end()
{
    // Check that begin was called
    assert(m_bDrawing && "Must call begin before end");

    // flush buffer and render
    flush();

    m_bDrawing = false;
}

// void SpriteBatch::setShader(const sf::Shader *shader)
// {
//     m_states.shader = shader;
// }

void SpriteBatch::draw(sf::ConstTexturePtr pTexture, float x, float y)
{
    sf::Vector2u texSize = pTexture->getSize();

    // Delegate to other function
    draw(pTexture, x, y, texSize.x, texSize.y);
}

void SpriteBatch::draw(sf::ConstTexturePtr pTexture, const sf::Vector2f &position, const sf::Vector2f &bounds)
{
    this->draw(pTexture, position.x, position.y, bounds.x, bounds.y);
}

void SpriteBatch::draw(sf::ConstTexturePtr pTexture, float x, float y, float width, float height)
{
    // Check that begin was called
    assert(m_bDrawing && "Must call begin before draw");

    const sf::Texture* newTexture = pTexture.get();

    if(newTexture != m_states.texture)
        switchTexture(newTexture);
    else if(m_numSprites >= m_maxSprites)
        flush();

    sf::Vertex* pQuad = getNextQuad();

    pQuad[0].position = sf::Vector2f(x, y);
    pQuad[1].position = sf::Vector2f(x + width, y);
    pQuad[2].position = sf::Vector2f(x + width, y + height);
    pQuad[3].position = sf::Vector2f(x, y + height);

    sf::Vector2u texSize = pTexture->getSize();

    pQuad[0].texCoords = sf::Vector2f(0, 0);
    pQuad[1].texCoords = sf::Vector2f(texSize.x, 0);
    pQuad[2].texCoords = sf::Vector2f(texSize.x, texSize.y);
    pQuad[3].texCoords = sf::Vector2f(0, texSize.y);

    ++m_numSprites;
}

void SpriteBatch::draw(const TextureRegion &region, float x, float y, float width, float height)
{
    assert(m_bDrawing && "Must call begin before draw");

    auto newTexture = region.getTexture().get();

    if(newTexture != m_states.texture)
        switchTexture(newTexture);
    else if(m_numSprites >= m_maxSprites)
        flush();

    sf::Vertex* pQuad = getNextQuad();

    pQuad[0].position = sf::Vector2f(x, y);
    pQuad[1].position = sf::Vector2f(x + width, y);
    pQuad[1].position = sf::Vector2f(x + width, y + height);
    pQuad[1].position = sf::Vector2f(x, y + height);

    pQuad[0].texCoords = sf::Vector2f(region.u1, region.v1);
    pQuad[1].texCoords = sf::Vector2f(region.u2, region.v1);
    pQuad[1].texCoords = sf::Vector2f(region.u2, region.v2);
    pQuad[1].texCoords = sf::Vector2f(region.u1, region.v2);
}

void SpriteBatch::flush()
{
    m_pRenderTarget->draw(&m_vertices[0], m_numSprites * VERTICES_IN_QUAD,
                         m_vertices.getPrimitiveType(), m_states);

    // No sprites remaining
    m_numSprites = 0;
}

void SpriteBatch::switchTexture(const sf::Texture *pTexture)
{
    if(m_vertices.getVertexCount() > 0)
        flush();

    // NOTE: Contains raw pointer, could be the source of errors
    m_states.texture = pTexture;
}

sf::Vertex *SpriteBatch::getNextQuad()
{
    return &m_vertices[m_numSprites * VERTICES_IN_QUAD];
}
