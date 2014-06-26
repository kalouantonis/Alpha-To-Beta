#include <Lua/LuaStateManager.h>
#include <Lua/ScriptExports.h>

#include <Utils/Helpers.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

#include <sstream>

#include <LuaPlus.h>

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
        // Unregister Luexports
        ScriptExports::unregisterAll();
        // Close lua state
        //lua_close(m_pLuaState);
        LuaPlus::LuaState::Destroy(m_pLuaState);
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
    CORE_ASSERT(s_pSingleton != nullptr);
    SAFE_DELETE(s_pSingleton);
}

LuaStateManager* LuaStateManager::get()
{
    CORE_ASSERT(s_pSingleton);
    return s_pSingleton;
}

bool LuaStateManager::init()
{
    // Create new lua state and initialize with stdlib
    m_pLuaState = LuaPlus::LuaState::Create(true);

    if(m_pLuaState == nullptr)
    {
        // lua_atpanic will be called, printing an error to stderr
        CORE_ERROR("Lua failed to initialize");
        return false;
    }

    // Register functions to global scope
    m_pLuaState->GetGlobals().RegisterDirect("execute_file", (*this), &LuaStateManager::executeFile);
    m_pLuaState->GetGlobals().RegisterDirect("execute_string", (*this), &LuaStateManager::executeString);
    
    // register other exports
    ScriptExports::registerAll();

    return true;
}

bool LuaStateManager::executeFile(const char* filename)
{
    int result = m_pLuaState->DoFile(filename);

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
        result = m_pLuaState->DoString(str);

        if(result != 0)
            setError(result);
    }
    else // If the string starts with '=', wrap the statement in the log function
    {
        // Populate buffer
        std::string buffer("log(");
        buffer += (str + 1);
        buffer += ')';

        result = m_pLuaState->DoString(str);
        if(result != 0)
            setError(result);
    }
}

LuaPlus::LuaObject LuaStateManager::getGlobalVars() const
{
    CORE_ASSERT(m_pLuaState);
    return m_pLuaState->GetGlobals();
}

LuaPlus::LuaObject LuaStateManager::createPath(const char* pathString, bool ignoreLastElement)
{
    StringVector splitPath;
    // Split using '.'
    split(pathString, splitPath, '.');
    if(ignoreLastElement)
        // Remove last element
        splitPath.pop_back();

    LuaPlus::LuaObject context = getGlobalVars();

    // Iterate over all element values
    for(const auto& element : splitPath)
    {
        // make sure global context is still valid
        if(context.IsNil())
        {
            CORE_ERROR("Something went wrong in createPath(). Bailing on (element == " + element + ")");
            break;
        }

        // grab whatever exists for this element
        LuaPlus::LuaObject curr = context.GetByName(element.c_str());
        
        if(!curr.IsTable())
        {
            // If the element is not a table and not null, we overwrite it
            if(!curr.IsNil())
            {
                CORE_WARNING("Ovewriting element '" + element + "' in table");
                //context[element.c_str()] = luabind::nil;
                context.SetNil(element.c_str());
            }

            // element was either nil or was overwritten, so add the new table
            context.CreateTable(element.c_str());
        }

        // Assign new context
        context = context.GetByName(element.c_str());
    }

    return context;
}

void LuaStateManager::setError(int errorNo)
{
    // Note LuaPlus usually throws exceptions, so we shouldn't be hitting this point

    // Get last line of code executed
    LuaPlus::LuaStackObject stackObj(m_pLuaState, -1);
    const char* errMsg = stackObj.GetString();

    if(errMsg)
    {
        m_lastError = errMsg;
        clearStack();
    }
    else
    {
        m_lastError = "Unknown lua parse error";
    }

    CORE_LOG("LUA", m_lastError);
}



void LuaStateManager::clearStack()
{
    // All stack elements are removed
    m_pLuaState->SetTop(0);
}
