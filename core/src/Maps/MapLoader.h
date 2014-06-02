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

    /**
     * @brief Load map from file
     * @details Load map from file, giving the asset directory so that the tiled map
     * can be loaded correctly
     * 
     * @param mapFile TMX map file to load from
     * @param assetDir Asset directory used
     */
    void load(const std::string& mapFile, const std::string& assetDir);
    /**
     * @brief Reload the whole map.
     * @details Will fail if load() has not been called previously.
     */
	void reload();
private:
    artemis::World& m_worldManager;
    // Used to create entities for map
    EntityFactory m_entityFactory;

    typedef std::unordered_map<int, TextureRegion> TileSetContainer;

    std::unordered_map<int, TileSetContainer> m_tileTextures;

    /**
     * @brief Load a tileset in to TextureLocator
     * 
     * @param assetDir Asset directory used
     * @param tileset Tileset TMX definition
     */
    void loadTileSet(const std::string& assetDir, const Tmx::Tileset* tileset);

    /**
     * @brief Load tile entities.
     * @details These are just the plain tiles defined in the map TMX file
     * 
     * @param layer Tile layer to load
     * @param tileWidth Tile width
     * @param tileHeight Tile height
     */
    void loadTileEntities(const Tmx::Layer* layer, int tileWidth, int tileHeight);

    /**
     * @brief Load object groups. Need tile height for y offset
     * 
     * @param pObjectGroup Object group to load
     * @param tileHeight Tile height. Used to define the correct offset for 
     * displaying items. This is due to issues with the tiled co-ordinate system
     */
    void loadObjectGroup(const Tmx::ObjectGroup* pObjectGroup, int tileHeight);

	// Previously loaded file
    std::string m_prevMapFile;
    std::string m_prevAssetDir;
};

#endif // MAP_LOADER_H
