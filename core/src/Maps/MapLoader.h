#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <unordered_map>
#include <Graphics/TextureRegion.h>

#include <Entities/EntityFactory.h>

// Predefs
namespace Tmx
{
class Layer;
class Tileset;
class ObjectGroup;
}

class WorldManager;

class MapLoader
{
public:
    MapLoader(WorldManager& m_worldManager);

    void load(const std::string& mapFile, const std::string& assetDir);
	void reload();
private:
    WorldManager& m_worldManager;
    // Used to create entities for map
    EntityFactory m_entityFactory;

    std::unordered_map<int, TextureRegion> m_tileTextures;

    void loadTileSet(const std::string& assetDir, const Tmx::Tileset* tileset);

    void loadTileEntities(const Tmx::Layer* layer,
		int tileWidth, int tileHeight, bool collidable);

    void loadObjectGroup(const Tmx::ObjectGroup* objectGroup);

	// Previously loaded file
    std::string m_prevMapFile;
    std::string m_prevAssetDir;
};

#endif // MAP_LOADER_H
