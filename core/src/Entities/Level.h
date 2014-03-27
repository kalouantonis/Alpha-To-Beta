#ifndef LEVEL_H
#define LEVEL_H

#include <Entities/EntityFactory.h>

class Level
{
public:
	Level(WorldManager& worldManager);

	void load(const std::string& filename);
	void reload(bool reloadResources = true, bool reloadEntities = true);

	EntityFactory& getEntityFactory() { return m_entityFactory; }

private:
	/**
	 * Entity factory instance
	 */
	EntityFactory m_entityFactory;

	artemis::EntityManager* m_entityManager;

	/**
	 * Used for loading level data
	 */
	XMLoader m_xmlLoader;

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