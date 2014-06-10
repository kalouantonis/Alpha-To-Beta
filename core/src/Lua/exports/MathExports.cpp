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

    // FIXME: Handle cast fail exception
    float x = luabind::object_cast<float>(luaVec["x"]);
    float y = luabind::object_cast<float>(luaVec["y"]);

    PhysicsLocator::convertToWorldCoords(x, y);

    // Set lua object
    luaVec["x"] = x;
    luaVec["y"] = y;
}

}
