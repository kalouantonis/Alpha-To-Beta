#include <Graphics/SpriteBatch.h>
#include <Graphics/TextureRegion.h>
#include <Utils/Logger.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <glm/glm.hpp>

const unsigned short VERTICES_IN_QUAD = 4;

SpriteBatch::SpriteBatch(sf::RenderTargetPtr renderTarget, int capacity)
    : m_pRenderTarget(renderTarget)
    , m_vertices(sf::Quads, capacity * VERTICES_IN_QUAD)
    , m_numSprites(0)
    , m_maxSprites(capacity)
    , m_bDrawing(false)
{
    // Use inverted transforms
    // m_states.transform = m_states.transform.scale(1.f, -1.f);
    //m_states.transform.scale(1.f, -1.f);
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::begin()
{
    // Make sure end wasn't called before begin
    CORE_ASSERT(!m_bDrawing && "Must call end before begin");

    m_bDrawing = true;
}

void SpriteBatch::end()
{
    // Check that begin was called
    CORE_ASSERT(m_bDrawing && "Must call begin before end");

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
    checkBatchState(pTexture.get());

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

void SpriteBatch::draw(const TextureRegion& region, float x, float y, float width, float height, 
                        float originX, float originY, float rotation)
{
    checkBatchState(region.getTexture().get());

    // Covert degrees to radians
    const float rad = glm::radians(rotation);

    // calculate left and top right corner points relative to origin
    const float worldOriginX = x + originX;
    const float worldOriginY = y + originY;
    float fx = width -originX;
    float fy = -originY;
    float fx2 = -originX;
    float fy2 = height - originY;

    // Apply scale
    // if(scaleX != 1 || scaleY != 1)
    // {
    //     fx *= scaleX;
    //     fy *= scaleY;
    //     fx2 *= scaleX;
    //     fy2 *= scaleY;
    // }

    // construct corner points, go counter clockwise from top left
    const float p1x = fx;
    const float p1y = fy;
    const float p2x = fx;
    const float p2y = fy2;
    const float p3x = fx2;
    const float p3y = fy2;
    const float p4x = fx2;
    const float p4y = fy;

    float x1, y1;
    float x2, y2;
    float x3, y3;
    float x4, y4;

    // apply rotation
    if(rotation != 0.f)
    {
        const float sinval = glm::sin(rad);
        const float cosval = glm::cos(rad);

        x2 = cosval * p1x - sinval * p1y;
        y2 = sinval * p1x + cosval * p1y;

        x3 = cosval * p2x - sinval * p2y;
        y3 = sinval * p2x + cosval * p2y;

        x4 = cosval * p3x - sinval * p3y;
        y4 = sinval * p3x + cosval * p3y;

        x1 = x2 + (x4 - x3);
        y1 = y4 - (y3 - y2);
    }
    else 
    {
        x1 = p4x;
        y1 = p4y;

        x2 = p1x;
        y2 = p1y;

        x3 = p2x;
        y3 = p2y;

        x4 = p3x;
        y4 = p3y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    sf::Vertex* pQuad = getNextQuad();

    pQuad[0].position = sf::Vector2f(x1, y1);
    pQuad[1].position = sf::Vector2f(x2, y2);
    pQuad[2].position = sf::Vector2f(x3, y3);
    pQuad[3].position = sf::Vector2f(x4, y4);

     // Texture Vertices
    pQuad[0].texCoords = sf::Vector2f(region.u1, region.v1);
    pQuad[1].texCoords = sf::Vector2f(region.u2, region.v1);
    pQuad[2].texCoords = sf::Vector2f(region.u2, region.v2);
    pQuad[3].texCoords = sf::Vector2f(region.u1, region.v2);

    ++m_numSprites;
}

void SpriteBatch::draw(const TextureRegion &region, float x, float y, float width, float height)
{
    checkBatchState(region.getTexture().get());

    sf::Vertex* pQuad = getNextQuad();

    // Position Vertices
    pQuad[0].position = sf::Vector2f(x, y);
    pQuad[1].position = sf::Vector2f(x + width, y);
    pQuad[2].position = sf::Vector2f(x + width, y + height);
    pQuad[3].position = sf::Vector2f(x, y + height);

    // Texture Vertices
    pQuad[0].texCoords = sf::Vector2f(region.u1, region.v1);
    pQuad[1].texCoords = sf::Vector2f(region.u2, region.v1);
    pQuad[2].texCoords = sf::Vector2f(region.u2, region.v2);
    pQuad[3].texCoords = sf::Vector2f(region.u1, region.v2);

    ++m_numSprites;
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

void SpriteBatch::checkBatchState(const sf::Texture* const pTexture)
{
    CORE_ASSERT(m_bDrawing && "Must call begin before draw");

    if(pTexture != m_states.texture)
        switchTexture(pTexture);
    else if(m_numSprites >= m_maxSprites)
        flush();
}

sf::Vertex *SpriteBatch::getNextQuad()
{
    return &m_vertices[m_numSprites * VERTICES_IN_QUAD];
}
