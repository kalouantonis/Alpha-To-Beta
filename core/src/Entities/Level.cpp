#include <Entities/Level.h>

#include <Artemis/EntityManager.h>
#include <Artemis/World.h>

#include <boost/filesystem.hpp>

#include <Entities/WorldLocator.h>

#include <Lua/exports/EventExports.h>

#include <Resources/ResourceDef.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

using namespace boost;

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
	filesystem::path filePath(assetDir);

	if(filesystem::exists(filePath))
	{
		if(filesystem::is_regular_file(filePath))
		{
			// Load single asset
			try 
			{
				// Use Asset Directory as ID. Also, since its a regular file,
				// load it
				loadTexture(assetDir, assetDir);
			}
			catch(const std::runtime_error& e)
			{
				CORE_ERROR(e.what());
			}
		}
		else if(filesystem::is_directory(filePath))
		{
			std::vector<filesystem::path> fileVec;

			// Recurse directories
			std::copy(
				filesystem::directory_iterator(filePath),
				filesystem::directory_iterator(),
				std::back_inserter(fileVec)
			);

			for(const auto& file : fileVec)
			{
				// TODO: Support more extensions
				if(filesystem::is_regular_file(file) && 
                    (file.extension().generic_string() == ".png"))
                {
					loadTexture(
						// use generic file name for compatibility
						file.generic_string(), 
						// Use native file name
						file.string()
					);

				}
			}
		}
		else
		{
			CORE_ERROR(assetDir + ": No directories or files found.");
			return false;
		}
	}
	else
	{
		CORE_ERROR(assetDir + ": Asset folder does not exist");
		return false;
	}

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

