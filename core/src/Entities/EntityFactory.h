#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Resources/GenericObjectFactory.h>
#include <Resources/XMLoader.h>

#include <Components/ParsedComponent.h>
#include <Systems/WorldManager.h>

// ID Used for invalid entities
const long INVALID_ENTITY = -666;

typedef GenericObjectFactory<std::string, ParsedComponent> ComponentFactory;

/**
 * @brief Creates new entities from files.
 * @details Loads components from entity XML files
 * 
 */
class EntityFactory
{
public:
    EntityFactory(WorldManager& worldManager);
    ~EntityFactory();

    void load(const std::string& path, bool recurse = true);
    artemis::Entity& loadFromFile(const std::string& filename);

    const ComponentFactory& getComponentFactory() { return m_componentFactory; }

protected:
    ParsedComponent* createComponent(const tinyxml2::XMLElement* pElement);

    // Use component family ID
    ComponentFactory m_componentFactory;


private:
    // Store world reference
    WorldManager& m_worldManager;
    XMLoader m_xmlLoader;

    void invalidateEntity(artemis::Entity& entity);
};

#endif // ENTITYFACTORY_H
