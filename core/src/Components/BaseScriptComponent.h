#ifndef _BASE_SCRIPT_COMPONENT_H_
#define _BASE_SCRIPT_COMPONENT_H_

#include <Components/ParsedComponent.h>

#include <luabind/object.hpp>
#include <string>

class BaseScriptComponent: public ParsedComponent
{
public:
    BaseScriptComponent();
    virtual ~BaseScriptComponent();

    virtual bool load(const tinyxml2::XMLElement* pElement) override; 

    static const char* g_name;
    virtual const char* getName() const override { return g_name; }

    bool hasConstructor() const { return !m_scriptConstructorName.empty(); }
    bool hasDestructor() const { return !m_scriptDestructorName.empty(); }
    bool hasUpdateFunction() const { return !m_scriptUpdateFunctionName.empty(); }

    void callConstructor();
    void callDestructor();
    void callUpdate(float deltaTime);

private:
    std::string m_scriptObjectName;
    std::string m_scriptConstructorName;
    std::string m_scriptDestructorName;
    std::string m_scriptUpdateFunctionName;

    luabind::object m_scriptObject;
    luabind::object m_scriptConstructor;
    luabind::object m_scriptDestructor;
    luabind::object m_scriptUpdateFunction;

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
};

#endif // _BASE_SCRIPT_COMPONENT_H_
