#include <Components/BaseScriptComponent.h>

#include <Lua/LuaStateManager.h>

#include <Utils/Logger.h>
#include <Utils/String.h>

#include <tinyxml2.h>

#include <luabind/function.hpp>

#include <boost/algorithm/string.hpp>

static const char* METATABLE_NAME = "BaseScriptComponentMetaTable";
const char* BaseScriptComponent::g_name = "BaseScriptComponent";

BaseScriptComponent::BaseScriptComponent()
    //: m_scriptObject(luabind::nil)
    //, m_scriptDestructor(luabind::nil)
    : m_bConstructorCalled(false)
    , m_bDestructorCalled(false)
    , m_updateFrequency(0.f)
    , m_currTime(0.f)
{
}

BaseScriptComponent::~BaseScriptComponent()
{
//    // Call the script destruction if it exists
//    if(luabind::type(m_scriptDestructor) == LUA_TFUNCTION)
//    {
//        // TODO: Ensure that destructor is actually called
//        luabind::call_function<void> destructorFunc(m_scriptDestructor, m_scriptObject);
//    }
    if(hasDestructor())
        callDestructor();

    // Clear out script object
    //m_scriptObject = luabind::nil;

    // If we are given the path for this script object, set it to nil
    if(!m_scriptObjectName.empty())
    {
        m_scriptObjectName += " = nil";
        LuaStateManager::get()->executeString(m_scriptObjectName.c_str());
    }
}

void BaseScriptComponent::callConstructor()
{
    // Ensure that we havent already called the constructor and that the 
    // object is a function
    if(!m_bConstructorCalled && luabind::type(m_scriptConstructor) == LUA_TFUNCTION)
    {
        luabind::call_function<void>(m_scriptConstructor, m_scriptObject);

        m_bConstructorCalled = true;
    }
}

void BaseScriptComponent::callDestructor()
{
    if(!m_bDestructorCalled && luabind::type(m_scriptDestructor) == LUA_TFUNCTION)
    {
        luabind::call_function<void>(m_scriptDestructor, m_scriptObject);

        m_bDestructorCalled = true;
    }
}

void BaseScriptComponent::callUpdate(float deltaTime)
{
    m_currTime += deltaTime;

    // Assure that we are calling the item at the correct frequency
    if(m_currTime >= m_updateFrequency)
    {
        luabind::call_function<void>(m_scriptUpdateFunction, m_scriptObject);

        // Reset time
        m_currTime = 0;
    }
}

bool BaseScriptComponent::load(const tinyxml2::XMLElement* pElement) 
{
    LuaStateManager* pStateManager = LuaStateManager::get();
    assert(pStateManager != nullptr);
    
    // TODO: May not need to load file
    const tinyxml2::XMLElement* pChildElement = pElement->FirstChildElement("File");
    if(!pChildElement)
    {
        CORE_ERROR("No <File> tag in BaseScriptComponent XML");
        return false;
    }

    std::string file = make_string(pChildElement->GetText());

    if(file.empty())
    {
        CORE_ERROR("<File> tag exists but is not actually defined");
        return false;
    }

    // Trim whitespace
    boost::algorithm::trim(file);

    if(!LuaStateManager::get()->executeFile(file.c_str()))
    {
        CORE_ERROR("Failed to execute lua file: " + file);
        return false;
    }

    pChildElement = pElement->FirstChildElement("ScriptObject");
    if(!pChildElement)
    {
        CORE_ERROR("No <ScriptObject> tag in XML");
        return true;
    }

    // Get ScriptObject attributes
    m_scriptObjectName = make_string(pChildElement->Attribute("var"));
    m_scriptConstructorName = make_string(pChildElement->Attribute("constructor"));
    m_scriptDestructorName = make_string(pChildElement->Attribute("destructor"));
    m_scriptUpdateFunctionName = make_string(pChildElement->Attribute("update"));

    // Get update frequency
    pChildElement->QueryFloatAttribute("frequency", &m_updateFrequency);

    if(!m_scriptObjectName.empty())
    {
        m_scriptObject = pStateManager->createPath(m_scriptObjectName.c_str());

        //if(luabind::type(m_scriptObject) != LUA_TNIL)
        if(!m_scriptObject.is_valid())
        {
            createScriptObject();
        }
    }

    // The script constructor will also cause a lua object to be created if one wasn't created in the
    // previous step. The string is treated as a function
    if(!m_scriptConstructorName.empty())
    {
        m_scriptConstructor = pStateManager->getGlobalVars()[m_scriptConstructorName.c_str()];
        if(luabind::type(m_scriptConstructor) == LUA_TFUNCTION &&
           //luabind::type(m_scriptObject) == LUA_TNIL)
           m_scriptObject.is_valid())
        {
            // The script object could be nil if there was not scriptObject attribute. 
            // The lua object will be created here
            m_scriptObject = luabind::newtable(pStateManager->getLuaState());
            createScriptObject();
        }
    }

    // The scriptDestructor is called when the C++ scriptObject instance is destroyed
    if(!m_scriptDestructorName.empty())
    {
        m_scriptDestructor = pStateManager->getGlobalVars()[m_scriptDestructorName.c_str()];
    }

    if(!m_scriptUpdateFunctionName.empty())
    {
        m_scriptUpdateFunction = pStateManager->getGlobalVars()[m_scriptUpdateFunctionName.c_str()];
    }

    // ScriptData element
    pChildElement = pElement->FirstChildElement("ScriptData");
    if(pChildElement)
    {
        if(luabind::type(m_scriptObject) == LUA_TNIL)
        {
            CORE_ERROR("ScriptObject can not be nil when ScriptData has been defined");
            return false;
        }

        for(const tinyxml2::XMLAttribute* pAttribute = pChildElement->FirstAttribute(); 
                pAttribute != NULL; pAttribute = pAttribute->Next())
        {
            // Set string
            m_scriptObject[pAttribute->Name()] = pAttribute->Value(); 
        }
    }

    return true;
}

void BaseScriptComponent::createScriptObject()
{
    LuaStateManager* pStateManager = LuaStateManager::get();
    assert(pStateManager != nullptr);
    assert(m_scriptObject.is_valid());

    // Get meta table
    luabind::object metaTableObject = pStateManager->getGlobalVars()[METATABLE_NAME];
    assert(luabind::type(metaTableObject) != LUA_TNIL);

    // Set __object to reference this class instance
    // TODO: Make this shit work
    //metaTableObject["__object"] = this;
    // Set meta table
    luabind::setmetatable(m_scriptObject, metaTableObject);
}
