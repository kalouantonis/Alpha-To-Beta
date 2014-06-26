#include <Lua/exports/EntityExports.h>

#include <Components/Transform.h>

#include <Entities/EntityFactory.h>
#include <Entities/WorldLocator.h>

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

    sf::Vector2f position(
        luaPosition["x"].GetFloat(),
        luaPosition["y"].GetFloat()
    );

    artemis::Entity& entity = WorldLocator::getObject()->createEntity();

    // Create entity
    if(!EntityFactory::get().loadFromFile(entityResource, entity))
    {
        CORE_ERROR("Failed to load entity from file: " + std::string(entityResource));
        return INVALID_ENTITY_ID;
    }

    artemis::Component* transformComp = entity.getComponent<Transform>();

    if(!transformComp)
    {
        // Create new transform component if it doesnt exist
        entity.addComponent(new Transform(position.x, position.y));
    }

    // Commit entity changes
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
