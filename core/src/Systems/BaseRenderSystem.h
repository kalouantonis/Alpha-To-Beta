#ifndef _BASERENDERSYSTEM_H_
#define _BASERENDERSYSTEM_H_

#include<Artemis/EntitySystem.h>

#include <Graphics/SpriteBatch.h>

#include <unordered_map>
#include <map>

class IRenderable;
class Transform;

template <class T>
class BaseRenderSystem: public artemis::EntitySystem
{
public:
	// In the deriving class, its best for the user to declare the type of component it
	// will be processing
	// e.g. addComponentType<Renderable>()
	BaseRenderSystem(SpriteBatch& spriteBatch);
	virtual ~BaseRenderSystem();

private:
	virtual void added(artemis::Entity& e) final;
	virtual void removed(artemis::Entity& e) final;
	virtual void begin() final;
	virtual void end() final;
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag) final;
	virtual bool checkProcessing() final;

	SpriteBatch& m_spriteBatch;

	typedef std::pair<const T*, const Transform*> DrawablePair;
	typedef std::unordered_map<int, DrawablePair> DrawableMap;

	// Ordered map
	std::map<int, DrawableMap> m_drawables;
};

#endif