#include <Entities/Level.h>

#include <Artemis/EntityManager.h>
#include <Artemis/World.h>

#include <tinydir.h>

#include <Entities/WorldLocator.h>

#include <Lua/exports/EventExports.h>

#include <Resources/ResourceDef.h>
#include <Utils/FileSystem.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

Level::Level()
    : m_mapLoader()
{
}

void Level::load(const std::string& filename)
{
	// Store previous file
	m_prevLevelFile = filename;

	// Load XML file
	const tinyxml2::XMLElement* pRoot = m_xmlLoader.loadAndGetRoot(
		filename.c_str()
	);

	if(!pRoot)
	{
		CORE_ERROR("Failed to load level file: " + filename);
		return;
	}

	// Load XML properties

	// Asset files
	const tinyxml2::XMLElement* childElem = pRoot->FirstChildElement("Assets");

	if(!childElem)
	{
		CORE_ERROR("No Asset element defined in " + filename);
		return;
	}

	std::string assetFile = make_string(childElem->GetText());

	if(assetFile.empty())
	{
		CORE_ERROR("No asset file defined in: " + filename);
		return;
	}

	trim(assetFile);

	// TODO: Use exceptions or something cleaner
	if(!loadAssets(assetFile))
	{
		return;
	}

	// Map file
	childElem = pRoot->FirstChildElement("MapFile");

	if(!childElem)
	{
		CORE_ERROR("No MapFile element defined in " + filename);
		return;
	}

	std::string mapFile = make_string(childElem->GetText());

	if(mapFile.empty())
	{
		CORE_ERROR("No map file defined in " + filename);
		return;
	}

	// Trim whitespace
	trim(mapFile);

    m_mapLoader.load(mapFile, assetFile);

	// Load constants....
}

void Level::reload(bool reloadResources, bool reloadEntities)
{
	CORE_ASSERT(!m_prevLevelFile.empty());

	if(reloadEntities)
	{
		CORE_LOG("LEVEL", "Removing all entities from manager...");
        WorldLocator::getObject()->getEntityManager()->removeAllEntities();
		// TODO: Reload all systems
	}

	if(reloadResources)
	{
		CORE_LOG("LEVEL", "Clearing textures...");
		// Clear texture locator
		TextureLocator::getObject()->clear();
	}
	
	// Re-register script events.
	// We're doing this so that old registered events are not
	// persisted after reload, causing lua to crash because it can not locate
	// the registered function
	InternalScriptExports::destroyEventExports();
	InternalScriptExports::initEventExports();

	CORE_LOG("LEVEL", "Reloading level...");
	load(m_prevLevelFile);
}

bool Level::loadAssets(const std::string& assetDir)
{
	tinydir_dir dir;

	if(tinydir_open(&dir, assetDir.c_str()) == -1)
	{
		CORE_ERROR("Error opening directory: " + assetDir);

		tinydir_close(&dir);
		return false;
	}

	while(dir.has_next)
	{
		tinydir_file file;
		if(tinydir_readfile(&dir, &file) == -1)
		{
			// Error
			CORE_ERROR("Error opening file: " + std::string(file.path));
			continue;
		}

		if(std::string(file.extension) == "png")
		{
			loadTexture(file.path, file.path);
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	return true;
}

void Level::loadTexture(const std::string& id, const std::string& file)
{
	try
	{
		TextureLocator::getObject()->load(id, file);
		
		CORE_DEBUG("Loaded texture: " + file);
	}
	catch(const std::runtime_error& e)
	{
		CORE_ERROR(e.what());
	}
}

