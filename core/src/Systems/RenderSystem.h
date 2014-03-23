#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <entityx/System.h>
#include <Graphics/SpriteBatch.h>
//#include <list>

/*
TODO: 

- Group textures
- Layering using a map
- Quad tree

*/

class RenderSystem: public entityx::System<RenderSystem>/*, Receiver<RenderSystem>*/
{
public:
	RenderSystem(SpriteBatch& spriteBatch);

	// void configure(entityx::ptr<entityx::EventManager> events);

	void update(entityx::ptr<entityx::EntityManager> es,
		entityx::ptr<entityx::EventManager> event, float dt) override;

	// TODO: Include receivers for component<Renderable> added and removed 
	// and fill map of orders


private:
	SpriteBatch m_spriteBatch;

	//std::list<std::pair<Transform, Renderable> > m_drawedComponents;
	// Check if renderable entity has a transform component too, if so, add to render system
	// void receive(const ComponentAddedEvent<Renderable>& renderable);
};

#endif // RENDER_SYSTEM_H