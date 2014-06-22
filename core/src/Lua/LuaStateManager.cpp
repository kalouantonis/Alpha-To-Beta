#include <Lua/LuaStateManager.h>
#include <Lua/ScriptExports.h>

#include <Utils/Helpers.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

extern "C" 
{
    #include <lua.h>
    #include <lualib.h>
}

#include <luabind/open.hpp>
#include <luabind/function.hpp>

#include <sstream>

int _addFileAndLine(lua_State* pL)
{
    lua_Debug d;
    // Get top of stack
    lua_getstack(pL, 1, &d);
    lua_getinfo(pL, "Sln", &d);
    // Last call
    std::string err = lua_tostring(pL, -1);
    // Pop first item
    lua_pop(pL, 1);

    std::stringstream msg;
    msg << d.short_src << ":" << d.currentline;

    if(d.name != 0)
    {
        msg << "(" << d.namewhat << " " << d.name << ")";
    }
    msg << " " << err;
    lua_pushstring(pL, msg.str().c_str());
    return 1;
}

// Initialize state as null
LuaStateManager* LuaStateManager::s_pSingleton = nullptr;

LuaStateManager::LuaStateManager()
    : m_pLuaState(nullptr)
{
    // Register error callback
    luabind::set_pcall_callback(&_addFileAndLine);
}

LuaStateManager::~LuaStateManager()
{
    if(m_pLuaState)
    {
        // Unregister exports
        ScriptExports::unregisterAll();
        // Close lua state
        lua_close(m_pLuaState);
        m_pLuaState = nullptr;
    }
}

bool LuaStateManager::create()
{
    if(s_pSingleton)
    {
        CORE_WARNING("Overwriting LuaStateManager singleton");
        SAFE_DELETE(s_pSingleton);
    }

    s_pSingleton = new LuaStateManager();
    if(s_pSingleton)
        return s_pSingleton->init();

	return false;
}

void LuaStateManager::destroy()
{
    assert(s_pSingleton != nullptr);
    SAFE_DELETE(s_pSingleton);
}

LuaStateManager* LuaStateManager::get()
{
    assert(s_pSingleton);
    return s_pSingleton;
}

bool LuaStateManager::init()
{
    // Create new lua state
    m_pLuaState = luaL_newstate();

    if(m_pLuaState == nullptr)
    {
        // lua_atpanic will be called, printing an error to stderr
        CORE_ERROR("Lua failed to initialize");
        return false;
    }

    // Connect LuaBind to lua state
    luabind::open(m_pLuaState);

    // Load stdlib
    CORE_DEBUG("Loading lua base library");
    luaopen_base(m_pLuaState);
    CORE_DEBUG("Loading lua table library");
    luaopen_table(m_pLuaState);
    CORE_DEBUG("Loading lua math library");
    luaopen_math(m_pLuaState);
    CORE_DEBUG("Loading lua string library");
    luaopen_string(m_pLuaState);
    CORE_DEBUG("Loading lua io library");
    luaopen_io(m_pLuaState);
    CORE_DEBUG("Loading lua package library");
    luaopen_package(m_pLuaState);

#ifdef _DEBUG
    CORE_DEBUG("Loading lua debug library");
    luaopen_debug(m_pLuaState);
#endif

    // bind functions. Add to global scope
    luabind::module(m_pLuaState)
    [
        luabind::def("execute_file", &LuaStateManager::executeFile),
        luabind::def("execute_string", &LuaStateManager::executeString)
    ];

    // register other exports
    ScriptExports::registerAll();

    return true;
}

bool LuaStateManager::executeFile(const char* filename)
{
    int result = luaL_dofile(m_pLuaState, filename);

    if(result != 0)
    {
        // Call error
        setError(result);
        return false;
    }

    return true;
}

void LuaStateManager::executeString(const char* str)
{
    int result = 0;

    // Most strings are passed straight through the lua interpreter
    if(strlen(str) <= 1 || str[0] != '=')
    {
        // Execute string
        result = luaL_dostring(m_pLuaState, str);

        if(result != 0)
            setError(result);
    }
    else // If the string starts with '=', wrap the statement in the log function
    {
        // Populate buffer
        std::string buffer("log(");
        buffer += (str + 1);
        buffer += ')';

        result = luaL_dostring(m_pLuaState, buffer.c_str());
        if(result != 0)
            setError(result);
    }
}

luabind::object LuaStateManager::getGlobalVars() const
{
    assert(m_pLuaState);
    return luabind::globals(m_pLuaState);
}

luabind::object LuaStateManager::createPath(const char* pathString, bool ignoreLastElement)
{
    StringVector splitPath;
    // Split using '.'
    split(pathString, splitPath, '.');
    if(ignoreLastElement)
        // Remove last element
        splitPath.pop_back();

    luabind::object context = getGlobalVars();

    // Iterate over all element values
    for(const auto& element : splitPath)
    {
        // make sure global context is still valid
        if(luabind::type(context) == LUA_TNIL)
        {
            CORE_ERROR("Something went wrong in createPath(). Bailing on (element == " + element + ")");
            break;
        }

        // grab whatever exists for this element
        luabind::object curr = context[element.c_str()];
        
        if(luabind::type(curr) != LUA_TTABLE)
        {
            // If the element is not a table and not null, we overwrite it
            if(luabind::type(curr) != LUA_TNIL)
            {
                CORE_WARNING("Ovewriting element '" + element + "' in table");
                context[element.c_str()] = luabind::nil;
            }

            // element was either nil or was overwritten, so add the new table
            context[element.c_str()] = luabind::newtable(m_pLuaState);
        }

        // Assign new context
        context = context[element.c_str()];
    }

    return context;
}

void LuaStateManager::setError(int errorNo)
{
    // Get last line of code executed
    const char* errMsg = lua_tostring(m_pLuaState, -1);

    if(errMsg)
    {
        m_lastError = errMsg;
        clearStack();
    }
    else
    {
        m_lastError = "Unknown Lua parse error";
    }

    CORE_LOG("LUA", m_lastError);
}



void LuaStateManager::clearStack()
{
    // All stack elements are removed
    lua_settop(m_pLuaState, 0);
}
