#include <Systems/BaseRenderSystem.h>

#include <Components/Transform.h>
#include <Components/IRenderable.h>

#include <Entities/Utils.h>

#include <Utils/Logger.h>

#include <Artemis/World.h>

template <class T>
BaseRenderSystem<T>::BaseRenderSystem(SpriteBatch& spriteBatch)
	: m_spriteBatch(spriteBatch)
{
	// Only process entities with a transform component
	addComponentType<Transform>();
	addComponentType<T>();
}

template <class T>
BaseRenderSystem<T>::~BaseRenderSystem()
{
	m_drawables.clear();
}

template <class T>
void BaseRenderSystem<T>::added(artemis::Entity& e)
{
	// Get transform, should never fail
	const Transform* pTransform = safeGetComponent<Transform>(&e);
	CORE_ASSERT(pTransform != nullptr);
	
	T* pRenderable = safeGetComponent<T>(&e);
	CORE_ASSERT(pRenderable != nullptr);

	m_drawables[pRenderable->getDrawOrder()][e.getId()] = DrawablePair(
		pRenderable,
		pTransform
	);
}

template <class T>
void BaseRenderSystem<T>::removed(artemis::Entity& e)
{
	// Again, should never fail
	int zOrder = safeGetComponent<T>(&e)->getDrawOrder();

	auto orderFindIt = m_drawables.find(zOrder);

	if(orderFindIt != m_drawables.end())
	{
		DrawableMap& drawableMap = (*orderFindIt).second;
		DrawableMap::iterator drawableFindIt = drawableMap.find(e.getId());

		if(drawableFindIt != drawableMap.end())
		{
			// Remove from map
			drawableMap.erase(drawableFindIt);
		}

		// Check if while order map is empty
		if(drawableMap.empty())
		{
			m_drawables.erase(orderFindIt);
		}
	}
}

template <class T>
void BaseRenderSystem<T>::begin()
{
	m_spriteBatch.begin();
}

template <class T>
bool BaseRenderSystem<T>::checkProcessing()
{
	// No checking to do yet
	return true;
}

template <class T>
void BaseRenderSystem<T>::processEntities(artemis::ImmutableBag<artemis::Entity*> & bag)
{
	for(const auto& orderPair : m_drawables)
	{
		const DrawableMap& drawableMap = orderPair.second;

		for(const auto& drawable : drawableMap)
		{
			const DrawablePair& pair = drawable.second;

			T* pRenderable = pair.first;
			const Transform* pTransform = pair.second;

			// Update renderable before drawing it
			updateRenderable(pRenderable);

			m_spriteBatch.draw(pRenderable->getTextureRegion(),
				pTransform->position.x, pTransform->position.y, 
				pRenderable->getWidth(), pRenderable->getHeight(), 
				pTransform->origin.x, pTransform->origin.y, 
				pTransform->rotation
			);
		}
	}
}

template <class T>
void BaseRenderSystem<T>::end()
{
	m_spriteBatch.end();
}

template <class T>
float BaseRenderSystem<T>::getDelta() const 
{
	return world->getDelta();
}