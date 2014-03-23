#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Resources/GenericObjectFactory.h>
#include <entityx/Entity.h>
#include <Resources/XMLoader.h>
#include <memory>

// TODO: Move this eventually
typedef std::shared_ptr<entityx::EntityManager> EntityManagerPtr;
typedef std::shared_ptr<entityx::BaseComponent> ComponentPtr;

/**
 * @brief Creates new entities from files.
 * @details Loads components from entity XML files
 * 
 */
class EntityFactory
{
public:
    EntityFactory(EntityManagerPtr pEntityManager);
    ~EntityFactory() {}

    // Will need to recurse directories too
    void loadFromFile(const std::string& filename);
    void loadFromDirectory(const std::string& path, bool recurse = true);

protected:
    ComponentPtr createComponent(const tinyxml2::XMLElement* pElement);

    // Use component family ID
    GenericObjectFactory<entityx::BaseComponent::Family, entityx::BaseComponent> m_componentFactory;

private:
    EntityManagerPtr m_pEntityManager;
    XMLoader m_xmlLoader;
};

#endif // ENTITYFACTORY_H
