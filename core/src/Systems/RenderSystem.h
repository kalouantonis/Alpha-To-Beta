#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>
#include <Artemis/ImmutableBag.h>

#include <Graphics/SpriteBatch.h>

#include <Components/Transform.h>
#include <Components/Renderable.h>

#include <map>

//#include <list>

/*
TODO: 

- Group textures
- Layering using a map
- Quad tree

*/

class RenderSystem: public artemis::EntityProcessingSystem
{
public:
	RenderSystem(SpriteBatch& spriteBatch);
	virtual ~RenderSystem();

	// void configure(entityx::ptr<entityx::EventManager> events);

	// void update(entityx::ptr<entityx::EntityManager> es,
	// 	entityx::ptr<entityx::EventManager> event, float dt) override;

	virtual void begin() final;
	virtual void end() final;
	virtual void added(artemis::Entity& e) override;
	virtual void removed(artemis::Entity& e) override;

	virtual void processEntity(artemis::Entity& e) override;

	void dispose();


	// TODO: Include receivers for component<Renderable> added and removed 
	// and fill map of orders


private:
	SpriteBatch m_spriteBatch;

	artemis::ComponentMapper<Transform> m_transformMapper;
	artemis::ComponentMapper<Renderable> m_renderableMapper;

	//std::list<std::pair<Transform, Renderable> > m_drawedComponents;
	// Check if renderable entity has a transform component too, if so, add to render system
	// void receive(const ComponentAddedEvent<Renderable>& renderable);
	typedef std::pair<Renderable*, Transform*> DrawablePair;
	typedef std::map<long, DrawablePair> DrawableMap;

	DrawableMap m_drawables;
};

#endif // RENDER_SYSTEM_H