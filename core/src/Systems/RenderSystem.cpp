#include <Systems/RenderSystem.h>

#include <Components/Renderable.h>
#include <Components/Transform.h>

#include <Utils/Logger.h>

RenderSystem::RenderSystem(SpriteBatch& spriteBatch)
	: m_spriteBatch(spriteBatch)
{
}

// void RenderSystem::configure(entityx::ptr<entityx::EventManager> events)
// {
// 	events->subscribe<ComponentAddedEvent<Renderable> >(*this);
// }

void RenderSystem::update(entityx::ptr<entityx::EntityManager> es, 
	entityx::ptr<entityx::EventManager> event, float dt)
{
	// Begin rendering
	m_spriteBatch.begin();

	// Sort textures using begin and end iter 

	for(auto entity : es->entities_with_components<Transform, Renderable>())
	{
		TransformPtr transform = entity.component<Transform>();
		RenderablePtr renderable = entity.component<Renderable>();

		m_spriteBatch.draw(renderable->pTexture, transform->position, 
			transform->bounds);
	}

	// End rendering
	m_spriteBatch.end();
}

// void receive(const ComponentAddedEvent<Renderable>& renderable)
// {
	
// }
