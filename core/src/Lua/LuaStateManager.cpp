#include <Lua/LuaStateManager.h>

#include <Utils/Helpers.h>
#include <Utils/Logger.h>

#include <luabind/luabind.hpp>

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

bool LuaStateManager::init()
{
    // Create new lua state
    m_pLuaState = luaL_newstate();

    if(m_pLuaState == nullptr)
    {
        CORE_FATAL("Lua failed to initialize");
        return false;
    }

    // Connect LuaBind to lua state
    luabind::open(m_pLuaState);

    // bind functions
    luabind::module(m_pLuaState) 
    [
        luabind::def("execute_file", &LuaStateManager::executeFile),
        luabind::def("execute_string", &LuaStateManager::executeString)
    ];

    return true;
}

void LuaStateManager::executeFile(const char* filename)
{
    int result = luaL_dofile(m_pLuaState, filename);

    if(result != 0)
        // Call error
        setError(result);
}

void LuaStateManager::executeString(const char* str)
{
    int result = 0;

    // Most strings are passed straight through the lua interpretter
    if(strlen(str) <= 1 || str[0] != '=')
    {
        // Execute string
        result = luaL_dostring(m_pLuaState, str);

        if(result != 0)
            setError(result);
    }
    else // If the string starts with '=', wrap the statement in the print function
    {
        // Populate buffer
        std::string buffer("print(");
        buffer += (str + 1);
        buffer += ')';

        result = luaL_dostring(m_pLuaState, buffer.c_str());
        if(result != 0)
            setError(result);
    }
}

void LuaStateManager::setError(int errorNo)
{
    // Luabind usually throws exceptions. If this area is hit... well, we're screwed

    // Get last line of code executed
    const char* errMsg = lua_tostring(m_pLuaState, -1);

    if(errMsg)
    {
        m_lastError = errMsg;
        clearStack();
    }
    else
        m_lastError = "Unknown Lua parse error";

    CORE_ERROR(m_lastError);
}

void LuaStateManager::clearStack()
{
    // All stack elements are removed
    lua_settop(m_pLuaState, 0);
}