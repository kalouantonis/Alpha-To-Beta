#ifndef LUA_STATE_MANAGER_H
#define LUA_STATE_MANAGER_H

#include <string>
#include <luabind/object.hpp>

// FWD Defs
struct lua_State;

/////////////////////////////////////////////////////////////////

class LuaStateManager
{
public:
    static bool create();
    static void destroy();

    static LuaStateManager* get();

    bool init();
    void executeFile(const char* filename);
    void executeString(const char* str);

    const luabind::object& getGlobalVars() const;
    lua_State* getLuaState() const { return m_pLuaState; }

private:
    // State manager pointer for use by singleton
    static LuaStateManager* s_pSingleton;

    void setError(int errorNum);
    void clearStack();

    LuaStateManager();
    ~LuaStateManager();
    
    lua_State* m_pLuaState;
    /**
     * Last error to occur to lua interpretter
     */
    std::string m_lastError;
};

#endif // LUA_STATE_MANAGER_H
