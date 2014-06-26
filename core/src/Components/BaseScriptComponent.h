#ifndef _BASE_SCRIPT_COMPONENT_H_
#define _BASE_SCRIPT_COMPONENT_H_

#include <Components/ParsedComponent.h>

#include <string>

#include <LuaPlus.h>

namespace artemis
{
class Entity;
}

class BaseScriptComponent: public ParsedComponent
{
public:
    BaseScriptComponent();
    virtual ~BaseScriptComponent();

    virtual bool load(const tinyxml2::XMLElement* pElement) override; 

    static const char* g_name;
    virtual const char* getName() const override { return g_name; }

    /**
     * Initialize script component, giving it the parent entity
     * 
     * Don't worry about raw pointer, this component will be destroyed before
     * its parent entity
     */
    void initialize(artemis::Entity* pParentEntity);

    bool isInitialized() const { return (m_pParentEntity != nullptr); }

    bool hasConstructor() const { return m_scriptConstructor.IsFunction(); }
    bool hasDestructor() const { return m_scriptDestructor.IsFunction(); }
    bool hasUpdateFunction() const { return m_scriptUpdateFunction.IsFunction(); }

    void callConstructor();
    void callDestructor();
    void callUpdate(float deltaTime);

    /**
     * Register internal script functions to access and modify entity data
     */
    static void registerScriptFunctions();
    /**
     * Unregister all internal script functions from Lua VM
     */
    static void unregisterScriptFunctions();

private:
    std::string m_scriptObjectName;
    std::string m_scriptConstructorName;
    std::string m_scriptDestructorName;
    std::string m_scriptUpdateFunctionName;

    LuaPlus::LuaObject m_scriptObject;
    LuaPlus::LuaObject m_scriptConstructor;
    LuaPlus::LuaObject m_scriptDestructor;
    LuaPlus::LuaObject m_scriptUpdateFunction;

    artemis::Entity* m_pParentEntity;

    /**
     * Just a small check as to whether the constructor and destructor have been called.
     * Dont want to call them twice now do we?
     */
    bool m_bConstructorCalled;
    bool m_bDestructorCalled;

    /**
     * How frequently the script should be updated
     */
    float m_updateFrequency;
    /** 
     * Current delta time since last frequency reach
     */
    float m_currTime;

    void createScriptObject();

    // Functions for entity access through lua
    int getEntityId() const;

    void setPosition(LuaPlus::LuaObject newPos);
    LuaPlus::LuaObject getPosition() const;

	// Physics stuff
    void stopPhysics();
	void startPhysics();
	void stopCollisions();
	void startCollisions();
};

#endif // _BASE_SCRIPT_COMPONENT_H_
