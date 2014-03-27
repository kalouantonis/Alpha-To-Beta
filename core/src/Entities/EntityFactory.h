#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Resources/GenericObjectFactory.h>
#include <Resources/XMLoader.h>

#include <Components/ParsedComponent.h>
#include <Systems/WorldManager.h>

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
    // TODO: Move this to level
    // void reload();

protected:
    ParsedComponent* createComponent(const tinyxml2::XMLElement* pElement);

    // Use component family ID
    GenericObjectFactory<std::string, ParsedComponent> m_componentFactory;

    void loadFromFile(const std::string& filename);

private:
    // Store world reference
    WorldManager& m_worldManager;
    XMLoader m_xmlLoader;

    // std::string m_prevResource;
};

#endif // ENTITYFACTORY_H
