#include <Maps/MapLoader.h>

#include <assert.h>

#include <Systems/WorldManager.h>

#include <Components/Renderable.h>
#include <Components/Transform.h>
// #include <Components/TileBody.h>

#include <Resources/ResourceDef.h>
#include <Utils/Logger.h>
#include <Utils/FileSystem.h>

#include <TmxParser/Tmx.h>

#include <Artemis/Entity.h>

#include <boost/algorithm/string.hpp>

MapLoader::MapLoader(WorldManager &world)
    : m_worldManager(world)
    , m_entityFactory(world)
{

}

void MapLoader::load(const std::string &mapFile, const std::string &assetDir)
{
	// Store current file file
    m_prevMapFile = mapFile;
    m_prevAssetDir = assetDir;

    Tmx::Map map;

    // Parse map using asset directory
    map.ParseFile(mapFile);

    // Check for errors
    if(map.HasError())
    {
        CORE_ERROR("Error loading map " + mapFile + ": " + map.GetErrorText());
        return;
    }

    for(const Tmx::Tileset* tileset : map.GetTilesets())
    {

        loadTileSet(assetDir, tileset);
	}

	// load layers
    for(const Tmx::Layer* tileLayer : map.GetLayers())
	{
        // Only load if layer is visible
        if(tileLayer->IsVisible())
        {
            // if collidable, generate box2d static bodies
            bool collidable = tileLayer->GetProperties().HasProperty("collidable");


            loadTileEntities(tileLayer, map.GetTileWidth(), map.GetTileHeight(), collidable);
        }
	}

    for(const Tmx::ObjectGroup* objectGroup : map.GetObjectGroups())
    {
        loadObjectGroup(objectGroup);
    }

	// load all object layers and xml files. Also, must be of type ENTITY


    // Clear tile sets. Will remove references here. Don't want stuff dangling around now do we ;)
    m_tileTextures.clear();
}

void MapLoader::reload()
{
	// check that the map was already loaded once
    assert(!m_prevMapFile.empty() && !m_prevAssetDir.empty());

    load(m_prevMapFile, m_prevAssetDir);
}

void MapLoader::loadTileSet(const std::string &assetDir, const Tmx::Tileset* tileset)
{
    int tileWidth = tileset->GetTileWidth();
    int tileHeight = tileset->GetTileHeight();

    // Offset using margins too
    int xOffset = tileset->GetTileWidth() + tileset->GetSpacing();
    int yOffset = tileset->GetTileHeight() + tileset->GetSpacing();

    const Tmx::Image* image = tileset->GetImage();

    // Get tile set image. Should be preloaded from assets folder
    // Use path relative to asset directory
    sf::TexturePtr pTexture = TextureLocator::getObject()->get(assetDir + fs::nativeSeparator() + image->GetSource());

    if(!pTexture)
    {
        CORE_ERROR("Failed to load tileset: " + image->GetSource() + "\tNot preloaded");
        return;
    }

    int tilesetWidth = image->GetWidth();
    int tilesetHeight = image->GetHeight();

    // Tile ID's are fucked up and index from gid - 1
    int gid = tileset->GetFirstGid() - 1;

    // Take in to account if the tile + dimensions is large enough to fit in image
    for(int y = tileset->GetMargin() /*Offset by spacing*/; y + tileHeight < tilesetHeight; y += yOffset)
    {
        // Go through X coord first
        for(int x = tileset->GetMargin(); x + tileWidth < tilesetWidth; x += xOffset)
        {
            // set texture in to map using ID
            // Tilesets have constantly incrementing ID'S
            // Its good to make sure that im setting ID's correctly and parsing images correctly
            m_tileTextures[gid++] = TextureRegion(pTexture, x, y, tileWidth, tileHeight);
        }
    }
}

void MapLoader::loadTileEntities(const Tmx::Layer* layer, int tileWidth, int tileHeight, bool collidable)
{
    // NOTE: The parser automagically multiplies by tile width & height
    int layerHeight = layer->GetHeight();
    int layerWidth = layer->GetWidth();


    for(int x = 0; x < layerWidth; ++x)
    {
        for(int y = 0; y < layerHeight; ++y)
        {
            const Tmx::MapTile& tile = layer->GetTile(x, y);

            if(tile.id != 0 && tile.tilesetId != -1) // Valid tile ID
            {
                // Create new entity
                artemis::Entity& e = m_worldManager.createEntity();
                e.addComponent(new Transform(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
                // Insert new renderable using tileset id
                e.addComponent(new Renderable(m_tileTextures[tile.id], layer->GetZOrder(), tileWidth, tileHeight));

                if(collidable)
                {
                    // load bodies
                    // e.addComponent(new TileBody(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
                }

                // Commit entity changes
                e.refresh();
            }
        }
    }
}

void MapLoader::loadObjectGroup(const Tmx::ObjectGroup* objectGroup)
{
    for(const Tmx::Object* object : objectGroup->GetObjects())
    {
        // Dont reference, we need to convert
        std::string type = object->GetType();
        // convert to lower case
        boost::algorithm::to_lower(type);

        if(type == "entity")
        {
            const std::string& fileName = object->GetProperties().GetLiteralProperty("file");

            if(!fileName.empty())
            {
                artemis::Entity& entity = m_entityFactory.loadFromFile(fileName);

                if(entity.getUniqueId() == INVALID_ENTITY)
                {
                    CORE_ERROR("Invalid entity for: " + object->GetName());
                    continue;
                }

                // Safe to cast, we know its of that type anyway
                Transform* transformComp = static_cast<Transform*>(entity.getComponent<Transform>());

                if(!transformComp) // Transform does not already exist
                {
                    entity.addComponent(new Transform(object->GetX(), object->GetY(), object->GetWidth(), object->GetHeight()));
                }
                else
                {
                    // Override previous positions
                    transformComp->position.x = object->GetX();
                    transformComp->position.y = object->GetY();

                    if(transformComp->bounds.x == 0 && transformComp->bounds.y == 0) // no width & height
                    {
                        transformComp->bounds.x = object->GetWidth();
                        transformComp->bounds.y = object->GetHeight();
                    }
                }

                Renderable* renderableComp = static_cast<Renderable*>(entity.getComponent<Renderable>());

                if((renderableComp != NULL) && (renderableComp->width == 0.f && renderableComp->height == 0.f))
                {
                    renderableComp->width = object->GetWidth();
                    renderableComp->height = object->GetHeight();
                }
            }
            else
            {
                CORE_ERROR("No 'file' property in 'entity' object definition");
            }
        }
    }
}