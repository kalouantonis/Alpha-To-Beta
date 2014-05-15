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

namespace artemis
{
class World;
}

class MapLoader
{
public:
    MapLoader(artemis::World& m_worldManager);

    void load(const std::string& mapFile, const std::string& assetDir);
	void reload();
private:
    artemis::World& m_worldManager;
    // Used to create entities for map
    EntityFactory m_entityFactory;

    typedef std::unordered_map<int, TextureRegion> TileSetContainer;

    std::unordered_map<int, TileSetContainer> m_tileTextures;

    void loadTileSet(const std::string& assetDir, const Tmx::Tileset* tileset);

    void loadTileEntities(const Tmx::Layer* layer,
		int tileWidth, int tileHeight, bool collidable);

    /**
     * @brief Load object groups. Need tile height for y offset
     * @details [long description]
     * 
     * @param pObjectGroup [description]
     * @param tileHeight [description]
     */
    void loadObjectGroup(const Tmx::ObjectGroup* pObjectGroup, int tileHeight);

	// Previously loaded file
    std::string m_prevMapFile;
    std::string m_prevAssetDir;
};

#endif // MAP_LOADER_H
