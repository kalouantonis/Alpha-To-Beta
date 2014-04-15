#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <tmxparser.h>

class WorldManager;

class MapLoader
{
public:
	MapLoader(WorldManager& world);

	void load(const std::string& file);	
	void reload();
private:
	WorldManager& world;

	void loadTileEntities(const tmxparser::TmxLayer& layer,
		int tileWidth, int tileHeight, bool collidable);

	// Previously loaded file
	std::string m_prevFile;
};

#endif // MAP_LOADER_H
