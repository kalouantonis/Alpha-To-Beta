#include <Lua/exports/EntityExports.h>
#include <Lua/Utils.h>

#include <Components/Transform.h>
#include <Components/DynamicBody.h>

#include <Entities/EntityFactory.h>
#include <Entities/WorldLocator.h>
#include <Entities/Utils.h>

#include <Physics/PhysicsLocator.h>

#include <Utils/Logger.h>

#include <Artemis/Entity.h>

#include <SFML/System/Vector2.hpp>

namespace InternalScriptExports 
{

int createEntity(const char* entityResource, LuaPlus::LuaObject luaPosition)
{
    if(!luaPosition.IsTable())
    {
        CORE_LOG("LUA", "Invalid position object passed to create_entity function. Must be a table");
        return INVALID_ENTITY_ID;
    }

	sf::Vector2f position = tableToVec2<sf::Vector2f>(luaPosition);

    artemis::Entity& entity = WorldLocator::getObject()->createEntity();

    // Create entity
    if(!EntityFactory::get().loadFromFile(entityResource, entity))
    {
        CORE_ERROR("Failed to load entity from file: " + std::string(entityResource));
        return INVALID_ENTITY_ID;
    }

    Transform* transformComp = safeGetComponent<Transform>(&entity);

    if(!transformComp)
    {
        // Create new transform component if it doesn't exist
        entity.addComponent(new Transform(position.x, position.y));
    }
	else
	{
		CORE_DEBUG("Overriding transform with lua object");

		transformComp->position = position;
	}

    // Commit entity changes
    entity.refresh();

    CORE_LOG("LUA", "Created entity from: " + std::string(entityResource));

    return entity.getId();
}

int createEntityWithSize(const char* entityResource, LuaPlus::LuaObject luaPosition, LuaPlus::LuaObject luaSize)
{
	if(!luaPosition.IsTable())
	{
		CORE_LOG("LUA", "Invalid position object passed to create_entity.");
		return INVALID_ENTITY_ID;
	}

	if(!luaSize.IsTable())
	{
		CORE_LOG("LUA", "Invalid size object passed to create_entity.");
		return INVALID_ENTITY_ID;
	}

	sf::Vector2f position = tableToVec2<sf::Vector2f>(luaPosition);
	sf::Vector2f size = tableToVec2<sf::Vector2f>(luaSize);

	artemis::Entity& entity = WorldLocator::getObject()->createEntity();

	// Create entity
	if(!EntityFactory::get().loadFromFile(entityResource, entity))
	{
		CORE_ERROR("Failed to load entity from file: " + std::string(entityResource));
		return INVALID_ENTITY_ID;
	}

	Transform* pTransform = safeGetComponent<Transform>(&entity);

	if(!pTransform)
	{
		entity.addComponent(new Transform(position.x, position.y));
	}
	else 
	{
		pTransform->position = position;
	}

	// Get physics comp
	DynamicBody* pDynamicBody = safeGetComponent<DynamicBody>(&entity);

	if(pDynamicBody)
	{
		// Set dimensions, will be initialized later
		pDynamicBody->setDimensions(size.x, size.y);
	}
	else
	{
		entity.addComponent(new DynamicBody(size.x, size.y));
	}

	// commit entity changes
	entity.refresh();

	CORE_LOG("LUA", "Created entity from: " + std::string(entityResource));

	return entity.getId();
}


void removeEntity(int entityId)
{
    // Receive entity
    artemis::Entity& entity = WorldLocator::getObject()->getEntity(entityId); 
    CORE_LOG("LUA", "Removing entity: " + entity.toString());
    // Remove entity from world
    entity.remove();
}


}
