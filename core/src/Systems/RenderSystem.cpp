#include <Systems/RenderSystem.h>

#include <Artemis/Entity.h>

#include <Components/Renderable.h>
#include <Components/Transform.h>

#include <Utils/Logger.h>

RenderSystem::RenderSystem(SpriteBatch& spriteBatch)
	: m_spriteBatch(spriteBatch)
{
	addComponentType<Transform>();
	addComponentType<Renderable>();
}

RenderSystem::~RenderSystem()
{
    m_drawables.clear();
}

void RenderSystem::begin()
{
	// Sort drawables by texture

	m_spriteBatch.begin();
}

void RenderSystem::processEntities(artemis::ImmutableBag<artemis::Entity*> &entities)
{
    for(const auto& orderPair : m_drawables)
    {
        const DrawableMap& drawableMap = orderPair.second;

        for(const auto& drawable : drawableMap)
        {
            const DrawablePair& pair = drawable.second;

            const Renderable* renderable = pair.first;
            const Transform* transform = pair.second;

            m_spriteBatch.draw(renderable->getTextureRegion(),
                    transform->position.x, transform->position.y,
                    renderable->width, renderable->height,
                    transform->origin.x, transform->origin.y,
                    transform->rotation
            );
        }
    }
}

bool RenderSystem::checkProcessing()
{
    // No checking to be done yet
    return true;
}

void RenderSystem::end()
{
	m_spriteBatch.end();
}

void RenderSystem::added(artemis::Entity& e)
{
	// Handle adding to map
	artemis::Component* transform = e.getComponent<Transform>();
    Renderable* renderable = static_cast<Renderable*>(
                e.getComponent<Renderable>()
    );

    m_drawables[renderable->order][e.getId()] = DrawablePair(
        // Static casting is safe, as the type is guaranteed
        renderable,
        static_cast<Transform*>(transform)
    );


	// map[e.getId()] = std::make_pair(transform, renderable)
}

void RenderSystem::removed(artemis::Entity& e)
{
    int zOrder = static_cast<Renderable*>(e.getComponent<Renderable>())->order;

	// Attempt to find drawable
    std::map<int, DrawableMap>::iterator orderFindIt = m_drawables.find(zOrder);

    if(orderFindIt != m_drawables.end())
    {
        DrawableMap& drawableMap = (*orderFindIt).second;
        DrawableMap::iterator drawableFindIt = drawableMap.find(e.getId());

        if(drawableFindIt != drawableMap.end()) // exists
        {
            // Remove from map
            drawableMap.erase(drawableFindIt);
        }

        // Check if whole order map is empty
        if(drawableMap.empty())
        {
            // Erase from map
            m_drawables.erase(orderFindIt);
        }
    }

}

