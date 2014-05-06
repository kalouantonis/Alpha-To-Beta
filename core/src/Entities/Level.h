#ifndef LEVEL_H
#define LEVEL_H

#include <Entities/EntityFactory.h>
#include <Maps/MapLoader.h>

// fwd defs
namespace artemis
{
class EntityManager;
}

class Level
{
public:
	Level(artemis::World& worldManager);

	void load(const std::string& filename);
	void reload(bool reloadResources = true, bool reloadEntities = true);

	EntityFactory& getEntityFactory() { return m_entityFactory; }

private:
	/**
	 * Entity factory instance
	 */
	EntityFactory m_entityFactory;

    MapLoader m_mapLoader;

	/**
	 * @brief The manager of world entities
	 */
	artemis::EntityManager* m_entityManager;

	/**
	 * Used for loading level data
	 */
	XMLoader m_xmlLoader;

	/**
	 * @brief Load assets from asset folder in to texture holder
	 * 
	 * @param assetDir Asset directory to load from
	 * @return false if loading failed
	 */
    // TODO: Load assets using relative asset dir filename. Same goes for maps
	bool loadAssets(const std::string& assetDir);

	/**
	 * Location of game object definitions
	 */
	//std::string m_objectFolder;
	/**
	 * Previously used level file		
	 */
	std::string m_prevLevelFile;
};

#endif // LEVEL_H
