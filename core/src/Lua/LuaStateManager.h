#ifndef LUA_STATE_MANAGER_H
#define LUA_STATE_MANAGER_H

#include <SFML/System/NonCopyable.hpp>

#include <string>
#include <luabind/object.hpp>

// FWD Defs
struct lua_State;

/**
 * Singleton class tasked with managing the lua state
 */
class LuaStateManager: private sf::NonCopyable
{
public:
	/**
	 * Create state manager singleton, initialize lua state
	 * 
	 * @return true if creation success
	 */
    static bool create();
	/**
	 * Destroy state manager singleton, destroy lua state
	 */
    static void destroy();

    static LuaStateManager* get();

	/**
	 * Initialise lua state and register exports
	 * 
     * @return false if registering failed
     */
    bool init();
	/**
	 * Execute a given lua script file.
	 * 
     * @param filename Lua script to execute
     * @return false if loading failed 
     */
    bool executeFile(const char* filename);
	/**
	 * Execute a string with the lua interpreter
     * @param str String to execute
     */
    void executeString(const char* str);

	/**
	 * Get lua state global variables
     */
    luabind::object getGlobalVars() const;
	/**
	 * Get the lua interpreter state 
     */
    lua_State* getLuaState() const { return m_pLuaState; }

    /**
     * Takes a string and creates a table path to it. 
     *
     * E.g. If you pass in A.B.C, it will create a table called A with a single element called
     * B which has a single element called C
     */
    luabind::object createPath(const char* pathString, bool ignoreLastElement = false);

private:
    // State manager pointer for use by singleton
    static LuaStateManager* s_pSingleton;

	/**
	 * Log lua error
     */
    void setError(int errorNum);
	/**
	 * Clear lua state stack
     */
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
