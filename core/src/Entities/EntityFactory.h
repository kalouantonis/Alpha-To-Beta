#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Resources/GenericObjectFactory.h>
#include <Resources/XMLoader.h>

#include <Components/ParsedComponent.h>
// #include <Systems/WorldManager.h>

// fwd def
namespace artemis
{
class World;
class Entity;
}

// ID Used for invalid entities
typedef GenericObjectFactory<std::string, ParsedComponent> ComponentFactory;

/**
 * @brief Creates new entities from files.
 * @details Loads components from entity XML files
 * 
 */
class EntityFactory
{
public:
    EntityFactory(artemis::World& world);
    ~EntityFactory();

    void load(const std::string& path, bool recurse = true);
    bool loadFromFile(const std::string& filename, artemis::Entity& entity);
    bool loadFromFile(const std::string& filename);

    const ComponentFactory& getComponentFactory() { return m_componentFactory; }

protected:
    ParsedComponent* createComponent(const tinyxml2::XMLElement* pElement);

    // Use component family ID
    ComponentFactory m_componentFactory;


private:
    // Store world reference
    artemis::World& m_worldManager;
    XMLoader m_xmlLoader;
};

#endif // ENTITYFACTORY_H
