#include <Lua/exports/MathExports.h>
#include <Lua/LuaStateManager.h>

#include <Physics/PhysicsLocator.h>
#include <Utils/Logger.h>

#include <glm/glm.hpp>

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

float floor(float val)
{
	return glm::floor(val);
}

float sin(float val)
{
	return glm::sin(val);
}

float cos(float val)
{
	return glm::cos(val);
}

float tan(float val)
{
	return glm::tan(val);
}

template <typename T>
T abs(T val)
{
	return glm::abs(val);
}

float ceil(float val)
{
	return glm::ceil(val);
}

template <typename T>
T min(T a, T b)
{
	return glm::min(a, b);
}

template <typename T>
T max(T a, T b)
{
	return glm::max(a, b);
}

float round(float val)
{
	return glm::round(val);
}


}
