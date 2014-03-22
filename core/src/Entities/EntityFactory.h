#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Resources/GenericObjectFactory.h>
#include <Components/ParsedComponent.h>

// TODO: Move this eventually
typedef std::shared_ptr<entityx::EntityManager> EntityManagerPtr;

/**
 * @brief Creates new entities from files.
 * @details Loads components from entity XML files
 * 
 */
class EntityFactory
{
public:
    EntityFactory(EntityManagerPtr pEntityManager);
    virtual ~EntityFactory() {}

    // Will need to recurse directories too
    void loadEntity(const std::string& filename);

protected:
    virtual ComponentPtr createComponent(const tinyxml2::XMLElement* pElement);

    // Use component family ID
    // TODO: Check that new family is created for every component
    // that inherits from ParsedComponent
    GenericObjectFactory<ParsedComponent::Family, ParsedComponent> m_componentFactory;

private:
    EntityManagerPtr m_pEntityManager;
    XMLoader m_xmlLoader;
};

#endif // ENTITYFACTORY_H
