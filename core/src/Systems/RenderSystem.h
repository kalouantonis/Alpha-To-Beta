#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>
#include <Artemis/ImmutableBag.h>

#include <Graphics/SpriteBatch.h>

#include <Components/Transform.h>
#include <Components/Renderable.h>

#include <unordered_map>

//#include <list>

/*
TODO: 

- Group textures
- Layering using a map
- Quad tree

*/

class RenderSystem: public artemis::EntitySystem
{
public:
	RenderSystem(SpriteBatch& spriteBatch);
	virtual ~RenderSystem();

private:
	virtual void added(artemis::Entity& e) override;
	virtual void removed(artemis::Entity& e) override;
	virtual void begin() final;
	virtual void end() final;
    virtual void processEntities(artemis::ImmutableBag<artemis::Entity*> &entities) override;
    virtual bool checkProcessing() final;

	SpriteBatch m_spriteBatch;

	artemis::ComponentMapper<Transform> m_transformMapper;
	artemis::ComponentMapper<Renderable> m_renderableMapper;

	typedef std::pair<Renderable*, Transform*> DrawablePair;
    typedef std::unordered_map<int, DrawablePair> DrawableMap;

    // Ordered map
    std::map<int, DrawableMap> m_drawables;
};

#endif // RENDER_SYSTEM_H
