#include <Lua/ScriptExports.h>
#include <Lua/ScriptEvent.h>
#include <Lua/LuaStateManager.h>

// Exports
#include <Lua/exports/LoggerExports.h>
#include <Lua/exports/EventExports.h>
#include <Lua/exports/EntityExports.h>
#include <Lua/exports/MathExports.h>

#include <Utils/Logger.h>

#include <LuaObject.h>

namespace ScriptExports
{

template<class CallerType, class RetType>
void registerExport(const char* luaFuncName, RetType (CallerType::*func)())
{
    LuaStateManager::get()->getGlobalVars().RegisterDirect(luaFuncName, func);
}

template<class RetType>
void registerExport(const char* luaFuncName, RetType (*func)())
{
    LuaStateManager::get()->getGlobalVars().RegisterDirect(luaFuncName, func);
}

void registerAll()
{
	CORE_ASSERT(LuaStateManager::get());
    // Keep lua state reference for micro-optimization purposes.
    LuaPlus::LuaObject globals = LuaStateManager::get()->getGlobalVars();

    // Initialize script event listener
    InternalScriptExports::initEventExports();

    // Logger
    globals.RegisterDirect("log", &InternalScriptExports::luaLog);
    // Events
    globals.RegisterDirect("register_event_listener", &InternalScriptExports::registerEventListener);
    globals.RegisterDirect("remove_event_listener", &InternalScriptExports::removeEventListener);
    globals.RegisterDirect("queue_event", &InternalScriptExports::queueEvent);
    globals.RegisterDirect("trigger_event", &InternalScriptExports::triggerEvent);
    // Entities
    globals.RegisterDirect("create_entity", &InternalScriptExports::createEntity);
    globals.RegisterDirect("remove_entity", &InternalScriptExports::removeEntity);
    // Math
    globals.RegisterDirect("convert_to_world_coords", &InternalScriptExports::convertToWorldCoords);
}

void unregisterAll()
{
    // Destroy script event listener
    InternalScriptExports::destroyEventExports();
}

}
