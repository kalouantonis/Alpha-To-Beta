#ifndef SCRIPT_EXPORTS_H
#define SCRIPT_EXPORTS_H

namespace ScriptExports
{

/**
 * @brief Register a new class member callback to lua
 * 
 * @param luaFuncName Function name used in lua
 * @param func Callback method
 * @tparam CallerType The class type of the caller
 * @tparam The return type of the method
 */
template<class CallerType, class RetType>
void registerExport(const char* luaFuncName, RetType (CallerType::*func)());

/**
 * @brief Register a new function callback to lua
 * @param luaFuncName Function to be registed as in lua
 * @param func The function callback
 * @tparam RetType The return type of the function
 */
template<class RetType>
void registerExport(const char* luaFuncName, RetType (*func)());

/**
 * @brief Remove export from lua state
 * 
 * @param luaFuncName Lua function name
 */
void unregisterExport(const char* luaFuncName);

/**
 * Register all exports
 */
void registerAll();
/**
 * Unregister all exports
 */
void unregisterAll();

};

#endif // SCRIPT_EXPORTS_H
