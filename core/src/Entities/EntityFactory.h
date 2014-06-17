#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <Resources/GenericObjectFactory.h>
#include <Resources/XMLoader.h>

#include <Components/ParsedComponent.h>

#include <SFML/System/NonCopyable.hpp>
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
class EntityFactory: private sf::NonCopyable // Dis-allow copying
{
public:
    static EntityFactory& get();

    ~EntityFactory();

    template <class CompType>
    void registerComponent()
    {
        m_componentFactory.declare<CompType>(CompType::g_name);
    }

    /**
     * @brief load XML resources from directory
     *
     * @param path path of directory
     * @param recurse True if file directories are to be recursed
     */
    void load(const std::string& path, bool recurse = true);
    /**
     * @brief Load using XML file in to entity 
     * 
     * @param filename filename of XML resource
     * @param entity entity to load into
     * 
     * @return true if succeeded, false if failed
     */
    bool loadFromFile(const std::string& filename, artemis::Entity& entity);
    /**
     * @brief Load entity from XML and add to world
     * 
     * @param filename entity XML resource to load from
     * @return true if succeeded
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Get component factory
     */
    const ComponentFactory& getComponentFactory() { return m_componentFactory; }

protected:
    /**
     * @brief Create a component from XML element
     *
     * @param pElement Element to load from
     * @return New component. Null if failed
     */
    ParsedComponent* createComponent(const tinyxml2::XMLElement* pElement);

    // Use component family ID
    ComponentFactory m_componentFactory;

private:
    // Store world reference
//    artemis::World& m_worldManager;
    XMLoader m_xmlLoader;

    // Hide constructor and destructor
    EntityFactory();
};

#endif // ENTITYFACTORY_H
