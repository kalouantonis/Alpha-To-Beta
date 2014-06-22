#include <Lua/LuaStateManager.h>
#include <Lua/ScriptExports.h>

#include <Utils/Helpers.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

// TODO: Include specific headers
#include <luabind/luabind.hpp>
#include <luabind/lua_include.hpp>

// Initialize state as null
LuaStateManager* LuaStateManager::s_pSingleton = nullptr;

LuaStateManager::LuaStateManager()
    : m_pLuaState(nullptr)
{
    
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
    //luaL_openlibs(m_pLuaState);

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
