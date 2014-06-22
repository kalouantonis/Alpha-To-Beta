#include <Lua/exports/MathExports.h>

#include <Physics/PhysicsLocator.h>
#include <Utils/Logger.h>

#include <luabind/object.hpp>

namespace InternalScriptExports 
{

void convertToWorldCoords(const luabind::adl::object& luaVec)
{
    if(luabind::type(luaVec) != LUA_TTABLE)
    {
        CORE_LOG("LUA", "Invalid lua object provided to convert_to_world_coords.\n"
                "Must be of type table.");
        return;
    }

    try 
    {
        float x = luabind::object_cast<float>(luaVec["x"]);
        float y = luabind::object_cast<float>(luaVec["y"]);

        PhysicsLocator::convertToWorldCoords(x, y);

        // Set lua object
        luaVec["x"] = x;
        luaVec["y"] = y;

    }
    catch(const luabind::cast_failed& e)
    {
        CORE_LOG("LUA", "Failed to cast x and y co-ordinates in to vector."
                "\nInvalid type: " + std::string(e.info().name()));
    }
}

}
