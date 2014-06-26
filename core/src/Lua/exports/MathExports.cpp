#include <Lua/exports/MathExports.h>
#include <Lua/LuaStateManager.h>

#include <Physics/PhysicsLocator.h>
#include <Utils/Logger.h>

namespace InternalScriptExports 
{

void convertToWorldCoords(LuaPlus::LuaObject luaVec)
{
    if(!luaVec.IsTable())
    {
        CORE_LOG("LUA", "Invalid lua object provided to convert_to_world_coords.\n"
                "Must be of type table.");
        return;
    }

    float x = luaVec["x"].GetFloat();
    float y = luaVec["y"].GetFloat();

    PhysicsLocator::convertToWorldCoords(x, y);

    LuaPlus::LuaState* pLState = LuaStateManager::get()->getLuaState();

    // Set lua object
    luaVec["x"].AssignNumber(pLState, x);
    luaVec["y"].AssignNumber(pLState, y);
}

}
