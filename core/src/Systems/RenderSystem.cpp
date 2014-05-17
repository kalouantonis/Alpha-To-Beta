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

void RenderSystem::processEntity(artemis::Entity &e)
{
    // !TODO: Dont do this you idiot...
    DrawableMap::iterator findIt = m_drawables.find(e.getUniqueId());

    // Check that entity under given id exists in drawables
    if(findIt != m_drawables.end())
    {
        // Get pair
        DrawablePair& pair = (*findIt).second;

        Renderable* renderable = pair.first;
        Transform* transform = pair.second;

        // Draw renderable
        m_spriteBatch.draw(renderable->getTextureRegion(),
            transform->position.x, transform->position.y,
            renderable->width, renderable->height,
            transform->origin.x, transform->origin.y,
            //transform->scale.x, transform->scale.y,
            transform->rotation);
    }
}

void RenderSystem::end()
{
	m_spriteBatch.end();
}

void RenderSystem::added(artemis::Entity& e)
{
	// Handle adding to map
	artemis::Component* transform = e.getComponent<Transform>();
	artemis::Component* renderable = e.getComponent<Renderable>();

	if((transform != NULL) && (renderable != NULL))
	{
        m_drawables[e.getId()] = DrawablePair(
			// Static casting is safe, as the type is guaranteed
			static_cast<Renderable*>(renderable),
			static_cast<Transform*>(transform)
		);

	} 

	// map[e.getId()] = std::make_pair(transform, renderable)
}

void RenderSystem::removed(artemis::Entity& e)
{
	// Attempt to find drawable
	auto findIt = m_drawables.find(e.getUniqueId());

	if(findIt != m_drawables.end()) // exists
	{
		// Remove from map
		m_drawables.erase(findIt);
	}
}

