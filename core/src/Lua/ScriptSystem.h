#ifndef _SCRIPT_SYSTEM_H
#define _SCRIPT_SYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include <luabind/object.hpp>

#include <Components/BaseScriptComponent.h>

class ScriptSystem: public artemis::EntityProcessingSystem
{
public:
    ScriptSystem();
    ~ScriptSystem();

private:

    virtual void initialize() final;
    virtual void processEntity(artemis::Entity& e) final;

    virtual void added(artemis::Entity& e) final;
    virtual void removed(artemis::Entity& e) final;

    artemis::ComponentMapper<BaseScriptComponent> m_baseScriptMapper;
};

#endif // _SCRIPT_SYSTEM_H
