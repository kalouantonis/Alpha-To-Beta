    //
#include <Lua/ScriptExports.h>
#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

// Exports
#include <Lua/exports/LoggerExports.h>
#include <Lua/exports/EventExports.h>

#include <luabind/function.hpp>

namespace ScriptExports
{

template<class CallerType, class RetType>
void registerExport(const char* luaFuncName, RetType (CallerType::*func)())
{
    // Bind to global lua state
    luabind::module(LuaStateManager::get()->getLuaState())
    [
        luabind::def(luaFuncName, func)
    ];
}

template<class RetType>
void registerExport(const char* luaFuncName, RetType (*func)())
{
    luabind::module(LuaStateManager::get()->getLuaState())
    [
        luabind::def(luaFuncName, func)
    ];
}

void registerAll()
{
    // Keep lua state reference for micro-optimization purposes.
    lua_State* pLuaState = LuaStateManager::get()->getLuaState();

    luabind::module(pLuaState)
    [
        luabind::def("log", &InternalScriptExports::luaLog)
    ];
}

void unregisterAll()
{
}

}
