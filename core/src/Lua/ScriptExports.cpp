    //
#include <Lua/ScriptExports.h>
#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

// Exports
#include <Lua/exports/LoggerExports.h>
#include <Lua/exports/EventExports.h>
#include <Lua/exports/EntityExports.h>
#include <Lua/exports/MathExports.h>

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

    // Initialize script event listener
    InternalScriptExports::initEventExports();

    luabind::module(pLuaState)
    [
        // Logger
        luabind::def("log", &InternalScriptExports::luaLog),
        // Events
        luabind::def("register_event_listener", &InternalScriptExports::removeEventListener),
        luabind::def("remove_event_listener", &InternalScriptExports::removeEventListener),
        luabind::def("queue_event", &InternalScriptExports::queueEvent),
        luabind::def("trigger_event", &InternalScriptExports::triggerEvent),
        // Entities
        luabind::def("create_entity", &InternalScriptExports::createEntity),
        luabind::def("remove_entity", &InternalScriptExports::removeEntity)
        // Math
//        luabind::def("convert_to_world_coords", &InternalScriptExports::convertToWorldCoords)
    ];
}

void unregisterAll()
{
    // Destroy script event listener
    InternalScriptExports::destroyEventExports();
}

}
