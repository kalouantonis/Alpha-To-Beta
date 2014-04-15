#include <Maps/MapLoader.h>

#include <assert.h>

#include <Systems/WorldManager.h>

#include <Components/Renderable.h>
#include <Components/Transform.h>

#include <Resources/ResourceDef.h>

#include <Utils/Logger.h>

void MapLoader::load(const std::string &file)
{
	// Store current file file
	m_prevFile = file;

	tmxparser::TmxMap map;
	// load map
	if(tmxparser::parseFromFile(file, &map) != tmxparser::TmxReturn::kSuccess)
	{
		CORE_ERROR("Failed to load tilemap from: " + file);
		// Maybe use better error handling?
		return;
	}

	for(const auto& tileSet : map.tilesetCollection)
	{
		unsigned int tilesetWidth = tileSet.image.width;
		unsigned int tilesetHeight = tileSet.image.height;

		// Load tile set
		TextureLocator::getObject()->load(tileSet.image.source, tileSet.image.source);
	}

	// load layers
	for(const auto& tileLayer : map.layerCollection)
	{
		// if collidable, generate box2d static bodies
		bool collidable = tileLayer.propertyMap.find("collidable") != tileLayer.propertyMap.end();

		loadTileEntities(tileLayer, map.tileWidth, map.tileHeight, collidable);
	}

	// load all object layers and xml files. Also, must be of type ENTITY

}

void MapLoader::reload()
{
	// check that the map was already loaded once
	assert(!m_prevFile.empty());

	load(m_prevFile);
}

void MapLoader::loadTileEntities(const tmxparser::TmxLayer& layer, int tileWidth, int tileHeight, bool collidable)
{
	for(const auto& tile : layer.tiles)
	{
		// Add default components to entity
//		Renderable renderable = new Renderable()
	}
}
