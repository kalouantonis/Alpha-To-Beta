#include <Lua/exports/EntityExports.h>

#include <Components/Transform.h>

#include <Entities/EntityFactory.h>
#include <Entities/WorldLocator.h>

#include <Physics/PhysicsLocator.h>

#include <Utils/Logger.h>

#include <luabind/object.hpp>

#include <Artemis/Entity.h>

#include <SFML/System/Vector2.hpp>

namespace InternalScriptExports 
{

int createEntity(const char* entityResource, const luabind::adl::object& luaPosition)
{
    if(luabind::type(luaPosition) != LUA_TTABLE)
    {
        CORE_LOG("LUA", "Invalid position object passed to create_entity function. Must be a table");
        return INVALID_ENTITY_ID;
    }

    sf::Vector2f position(0.f, 0.f);

    try 
    {
        // Attempt to receive position from lua
        position.x = luabind::object_cast<float>(luaPosition["x"]);
        position.y = luabind::object_cast<float>(luaPosition["y"]);
    }
    catch(const luabind::cast_failed& e)
    {
        CORE_LOG("LUA", "Failed to cast position object vector to decimal."
                        "Attempting to load from resource, or set to (0,0)");
    }

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
