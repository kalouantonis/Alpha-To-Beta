#include <Entities/Level.h>

#include <Artemis/EntityManager.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <Resources/ResourceDef.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

using namespace boost;

Level::Level(WorldManager& worldManager)
	: m_entityFactory(worldManager)
    , m_mapLoader(worldManager)
    , m_entityManager(worldManager.getEntityManager())
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

	boost::algorithm::trim(assetFile);

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
	boost::algorithm::trim(mapFile);

    m_mapLoader.load(mapFile, assetFile);

	// Object files
	// childElem = pRoot->FirstChildElement("Objects");

	// if(!childElem)
	// {
	// 	CORE_ERROR("No Object element defined in " + filename);
	// 	return;
	// }

	// std::string objectFile = make_string(childElem->GetText());

	// if(objectFile.empty())
	// {
	// 	CORE_ERROR("No object file defined in: " + filename);
	// 	return;
	// }

	// // Trim whitespace
	// boost::algorithm::trim(objectFile);

	// // Load object directory using entity loader
	// m_entityFactory.load(objectFile);

	// Load constants....
}

void Level::reload(bool reloadResources, bool reloadEntities)
{
	assert(!m_prevLevelFile.empty());

	if(reloadEntities)
	{
		CORE_LOG("LEVEL", "Removing all entities from manager...");
		m_entityManager->removeAllEntities();
		// TODO: Reload all systems
	}

	if(reloadResources)
	{
		CORE_LOG("LEVEL", "Clearing textures...");
		// Clear texture locator
		TextureLocator::getObject()->clear();
	}

	CORE_LOG("LEVEL", "Reloading level...");
	load(m_prevLevelFile);
}

bool Level::loadAssets(const std::string& assetDir)
{
	// TODO: Move out of here, make generic file directory recurser
	filesystem::path filePath(assetDir);

	if(filesystem::exists(filePath))
	{
		if(filesystem::is_regular_file(filePath))
		{
			// Load single asset
			TextureLocator::getObject()->load(assetDir, assetDir);
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
					TextureLocator::getObject()->load(
							// use generic file name for compatibility
							file.generic_string(), 
							file.string()			// Use native file name
					);

					CORE_DEBUG("Loaded texture: " + file.string());
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

