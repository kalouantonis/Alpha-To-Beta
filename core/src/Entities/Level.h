#ifndef LEVEL_H
#define LEVEL_H

#include <Maps/MapLoader.h>

// fwd defs
namespace artemis
{
class EntityManager;
}

class Level
{
public:
	Level();

	void load(const std::string& filename);
	void reload(bool reloadResources = true, bool reloadEntities = true);

private:
    MapLoader m_mapLoader;

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
	bool loadAssets(const std::string& assetDir);
	void loadTexture(const std::string& id, const std::string& file);

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
