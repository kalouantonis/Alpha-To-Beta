#include <Systems/RenderSystem.h>

#include <Artemis/Entity.h>

#include <Components/Renderable.h>
#include <Components/Transform.h>

#include <Utils/Logger.h>

RenderSystem::RenderSystem(SpriteBatch& spriteBatch)
	: m_spriteBatch(spriteBatch)
{
	// Guarantee component types
	addComponentType<Transform>();
	addComponentType<Renderable>();
}

RenderSystem::~RenderSystem()
{
	dispose();
}

void RenderSystem::begin()
{
	// Sort drawables by texture

	// Begin drawing
	m_spriteBatch.begin();
}

void RenderSystem::processEntity(artemis::Entity &e)
{
	DrawableMap::iterator findIt = m_drawables.find(e.getUniqueId());

	// Check that entity under given id exists in drawables
	if(findIt != m_drawables.end())
	{
		// Get pair
		DrawablePair& pair = (*findIt).second;

		Renderable* renderable = pair.first;
		Transform* transform = pair.second;

		// Draw renderable
		m_spriteBatch.draw(renderable->pTexture, 
			transform->position.x, transform->position.y, 
			transform->bounds.x, transform->bounds.y);
	}
}

void RenderSystem::end()
{
	m_spriteBatch.end();
}

void RenderSystem::added(artemis::Entity& e)
{
	m_drawables[e.getUniqueId()] = DrawablePair(
		// Static casting is safe, as the type is guaranteed
		static_cast<Renderable*>(e.getComponent<Transform>()),
		static_cast<Transform*>(e.getComponent<Renderable>())
	);
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

void RenderSystem::dispose()
{
	if(!m_drawables.empty())
		m_drawables.clear();
}


// void RenderSystem::configure(entityx::ptr<entityx::EventManager> events)
// {
// 	events->subscribe<ComponentAddedEvent<Renderable> >(*this);
// }

// void RenderSystem::update(entityx::ptr<entityx::EntityManager> es, 
// 	entityx::ptr<entityx::EventManager> event, float dt)
// {
// 	// Begin rendering
// 	m_spriteBatch.begin();

// 	// Sort textures using begin and end iter 

// 	for(auto entity : es->entities_with_components<Transform, Renderable>())
// 	{
// 		TransformPtr transform = entity.component<Transform>();
// 		RenderablePtr renderable = entity.component<Renderable>();

// 		m_spriteBatch.draw(renderable->pTexture, transform->position, 
// 			transform->bounds);
// 	}

// 	// End rendering
// 	m_spriteBatch.end();
// }

// void receive(const ComponentAddedEvent<Renderable>& renderable)
// {
	
// }
