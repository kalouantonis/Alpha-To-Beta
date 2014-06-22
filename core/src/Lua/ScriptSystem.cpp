#include <Lua/ScriptSystem.h>

#include <Lua/LuaStateManager.h>

#include <Entities/Utils.h>

#include <Utils/Logger.h>

#include <Artemis/ComponentMapper.h>
#include <Artemis/Entity.h>

#include <luabind/nil.hpp>
#include <luabind/function.hpp>

ScriptSystem::ScriptSystem()
{
    addComponentType<BaseScriptComponent>();
}

ScriptSystem::~ScriptSystem()
{
    CORE_DEBUG("Unregistering script functions");
    BaseScriptComponent::unregisterScriptFunctions();
}

void ScriptSystem::initialize()
{
    m_baseScriptMapper.init(*world);

    CORE_DEBUG("Registering script functions...");
    BaseScriptComponent::registerScriptFunctions();
}

void ScriptSystem::added(artemis::Entity& e)
{
    BaseScriptComponent* pBaseScriptComp = safeGetComponent<BaseScriptComponent>(&e);

    // Initialize base script
    if(!pBaseScriptComp->isInitialized())
        pBaseScriptComp->initialize(&e);

    if(pBaseScriptComp->hasConstructor())
    {
        pBaseScriptComp->callConstructor();
    }
}

void ScriptSystem::processEntity(artemis::Entity& e)
{
    BaseScriptComponent* pBaseScriptComp = m_baseScriptMapper.get(e);

    if(pBaseScriptComp->hasUpdateFunction())
    {
        pBaseScriptComp->callUpdate(world->getDelta());
    }
}

void ScriptSystem::removed(artemis::Entity& e)
{
    BaseScriptComponent* pBaseScriptComp = safeGetComponent<BaseScriptComponent>(&e);

    if(pBaseScriptComp->hasDestructor())
    {
        pBaseScriptComp->callDestructor();
    }
}
