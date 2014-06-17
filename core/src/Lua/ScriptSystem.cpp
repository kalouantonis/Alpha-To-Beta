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

}

void ScriptSystem::initialize()
{
    m_baseScriptMapper.init(*world);
}

void ScriptSystem::added(artemis::Entity& e)
{
    BaseScriptComponent* pBaseScriptComp = safeGetComponent<BaseScriptComponent>(&e);

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
