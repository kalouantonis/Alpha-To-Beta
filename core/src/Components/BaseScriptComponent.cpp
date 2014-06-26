#include <Components/BaseScriptComponent.h>

#include <Components/Transform.h>
#include <Components/DynamicBody.h>
#include <Entities/Utils.h>

#include <Lua/LuaStateManager.h>
#include <Lua/Utils.h>

#include <Utils/Logger.h>
#include <Utils/String.h>

#include <Physics/CollisionMasks.h>

#include <Artemis/Entity.h>
#include <Artemis/Component.h>

#include <Box2D/Dynamics/b2Body.h>

#include <tinyxml2.h>

#include <boost/algorithm/string.hpp>

#include <LuaFunction.h>

static const char* METATABLE_NAME = "BaseScriptComponentMetaTable";
const char* BaseScriptComponent::g_name = "BaseScriptComponent";

BaseScriptComponent::BaseScriptComponent()
    : m_pParentEntity(nullptr)
    , m_bConstructorCalled(false)
    , m_bDestructorCalled(false)
    , m_updateFrequency(0.f)
    , m_currTime(0.f)

{
    LuaPlus::LuaState* pLuaState = LuaStateManager::get()->getLuaState();
    // Assign items as nil
    m_scriptConstructor.AssignNil(pLuaState);
    m_scriptDestructor.AssignNil(pLuaState);
    m_scriptUpdateFunction.AssignNil(pLuaState);
}

BaseScriptComponent::~BaseScriptComponent()
{
    callDestructor();

    // Clear out script object
    m_scriptObject.AssignNil(LuaStateManager::get()->getLuaState());

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
    if(!m_bConstructorCalled && hasConstructor())
    {
        LuaPlus::LuaFunction<void> func(m_scriptConstructor);
        func(m_scriptObject);

        m_bConstructorCalled = true;
    }
}

void BaseScriptComponent::callDestructor()
{
    if(!m_bDestructorCalled && hasDestructor())
    {
        LuaPlus::LuaFunction<void> func(m_scriptDestructor);
        func(m_scriptObject);

        m_bDestructorCalled = true;
    }
}

void BaseScriptComponent::callUpdate(float deltaTime)
{
    m_currTime += deltaTime;

    // Assure that we are calling the item at the correct frequency
    if(m_currTime >= m_updateFrequency && hasUpdateFunction())
    {
        LuaPlus::LuaFunction<void> func(m_scriptUpdateFunction);
        // Send actual delta
        func(m_currTime);

        // Reset time
        m_currTime = 0;
    }
}

bool BaseScriptComponent::load(const tinyxml2::XMLElement* pElement) 
{
    LuaStateManager* pStateManager = LuaStateManager::get();
    CORE_ASSERT(pStateManager != nullptr);
    
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

    if(!pStateManager->executeFile(file.c_str()))
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
        if(!m_scriptObject.IsNil())
        {
            createScriptObject();
        }
    }

    // The script constructor will also cause a lua object to be created if one wasn't created in the
    // previous step. The string is treated as a function
    if(!m_scriptConstructorName.empty())
    {
        m_scriptConstructor = pStateManager->getGlobalVars().Lookup(m_scriptConstructorName.c_str());
        if(m_scriptConstructor.IsFunction() && m_scriptObject.IsNil())
        {
            // The script object could be nil if there was not scriptObject attribute. 
            // The lua object will be created here
            m_scriptObject.AssignNewTable(pStateManager->getLuaState());
            createScriptObject();
        }
    }

    // The scriptDestructor is called when the C++ scriptObject instance is destroyed
    if(!m_scriptDestructorName.empty())
    {
        m_scriptDestructor = pStateManager->getGlobalVars().Lookup(m_scriptDestructorName.c_str());
    }

    if(!m_scriptUpdateFunctionName.empty())
    {
        m_scriptUpdateFunction = pStateManager->getGlobalVars().Lookup(m_scriptUpdateFunctionName.c_str());
    }

    // ScriptData element
    pChildElement = pElement->FirstChildElement("ScriptData");
    if(pChildElement)
    {
        if(m_scriptObject.IsNil())
        {
            CORE_ERROR("ScriptObject can not be nil when ScriptData has been defined");
            return false;
        }

        for(const tinyxml2::XMLAttribute* pAttribute = pChildElement->FirstAttribute(); 
                pAttribute != NULL; pAttribute = pAttribute->Next())
        {
            // Set string
            //m_scriptObject[pAttribute->Name()] = pAttribute->Value(); 
            m_scriptObject.SetString(pAttribute->Name(), pAttribute->Value());
        }
    }

    return true;
}

void BaseScriptComponent::initialize(artemis::Entity* pParentEntity)
{
    // Initialize parent entity
    m_pParentEntity = pParentEntity;
}

void BaseScriptComponent::createScriptObject()
{
    LuaStateManager* pStateManager = LuaStateManager::get();
    CORE_ASSERT(pStateManager != nullptr);
    CORE_ASSERT(!m_scriptObject.IsNil());

    // Get meta table
    LuaPlus::LuaObject metaTableObject = pStateManager->getGlobalVars().Lookup(METATABLE_NAME);
    CORE_ASSERT(!metaTableObject.IsNil());

    LuaPlus::LuaObject boxedPtr = pStateManager->getLuaState()->BoxPointer(this);
    boxedPtr.SetMetaTable(metaTableObject);
    // Give lua a reference to the C++ object
    m_scriptObject.SetLightUserData("__object", this);
    // Set meta table
    m_scriptObject.SetMetaTable(metaTableObject);
}

void BaseScriptComponent::registerScriptFunctions()
{   
	CORE_DEBUG("Registering script functions");

    LuaPlus::LuaObject metaTableObject = LuaStateManager::get()
        ->getGlobalVars().CreateTable(METATABLE_NAME);
    metaTableObject.SetObject("__index", metaTableObject);

    // Bind functions to meta-table ////////////////////////////////////////////////////////////////////////////////////
	// Entity operations
    metaTableObject.RegisterObjectDirect("get_entity_id", (BaseScriptComponent*)0, &BaseScriptComponent::getEntityId); 
	// Positions
	metaTableObject.RegisterObjectDirect("get_position", (BaseScriptComponent*)0, &BaseScriptComponent::getPosition);
	metaTableObject.RegisterObjectDirect("set_position", (BaseScriptComponent*)0, &BaseScriptComponent::setPosition);
	// Physics
	metaTableObject.RegisterObjectDirect("start_physics", (BaseScriptComponent*)0, &BaseScriptComponent::startPhysics);
	metaTableObject.RegisterObjectDirect("stop_physics", (BaseScriptComponent*)0, &BaseScriptComponent::stopPhysics);
	metaTableObject.RegisterObjectDirect("start_collisions", (BaseScriptComponent*)0, &BaseScriptComponent::startCollisions);
	metaTableObject.RegisterObjectDirect("stop_collisions", (BaseScriptComponent*)0, &BaseScriptComponent::stopCollisions);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void BaseScriptComponent::unregisterScriptFunctions()
{
	CORE_DEBUG("Unregistering script functions");

	LuaPlus::LuaObject metaTableObject = LuaStateManager::get()->getGlobalVars().Lookup(METATABLE_NAME);
	if(!metaTableObject.IsNil())
		// Leave nil for gc to clean up
		metaTableObject.AssignNil(LuaStateManager::get()->getLuaState());
}

int BaseScriptComponent::getEntityId() const
{
    if(isInitialized())
        return m_pParentEntity->getId();

    return -1;
}

void BaseScriptComponent::setPosition(LuaPlus::LuaObject newPos)
{
    artemis::Component* dynamicBody = m_pParentEntity->getComponent<DynamicBody>();

    if(dynamicBody != nullptr)
    {
        //static_cast<DynamicBody*>(dynamicBody)->body->SetPosition

    }
    else
    {
        artemis::Component* transform = m_pParentEntity->getComponent<Transform>();

        if(transform != nullptr)
        {
            //static_cast<Transform*>(transform)->position = pos;
        }
        else
        {
            CORE_LOG("LUA", "No components to set the position of");
        }
    }
}

LuaPlus::LuaObject BaseScriptComponent::getPosition() const
{
	CORE_ASSERT(isInitialized());

	LuaPlus::LuaObject ret;

	// Get transform component
	//Transform* pTransform = static_cast<Transform*>(m_pParentEntity->getComponent<Transform>());
	Transform* pTransform = safeGetComponent<Transform>(m_pParentEntity);

	if(pTransform)
		ret = vec2ToTable(pTransform->position);
	else 
		ret.AssignNil(LuaStateManager::get()->getLuaState());

	return ret;
}

void BaseScriptComponent::startPhysics()
{
	DynamicBody* pDynamicBody = safeGetComponent<DynamicBody>(m_pParentEntity);

	if(pDynamicBody)
		pDynamicBody->body->SetActive(true);
	else
		CORE_ERROR("Attempted to call start_physics on entity with no dynamic body");
}

void BaseScriptComponent::stopPhysics()
{
	DynamicBody* pDynamicBody = safeGetComponent<DynamicBody>(m_pParentEntity);

	if(pDynamicBody)
		pDynamicBody->body->SetActive(false);
	else 
		CORE_ERROR("Attempted to call stop_physics on entity with no dynamic body");
}

void BaseScriptComponent::startCollisions()
{
	DynamicBody* pDynamicBody = safeGetComponent<DynamicBody>(m_pParentEntity);

	if(pDynamicBody)
		changeFixtureFilterMaskFlags(pDynamicBody->body, COLLIDE);
	else
		CORE_ERROR("Attempted to call start_collisions on entity with no dynamic body");
}

void BaseScriptComponent::stopCollisions()
{
	DynamicBody* pDynamicBody = safeGetComponent<DynamicBody>(m_pParentEntity);
	
	if(pDynamicBody)
	{
		changeFixtureFilterMaskFlags(pDynamicBody->body, NO_COLLIDE);
	}
	else
	{
		CORE_ERROR("Attempted to call stop_collisions on entity with no dynamic body");
	}
}