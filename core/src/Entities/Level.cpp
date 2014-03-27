#include <Entities/Level.h>

#include <Artemis/EntityManager.h>
#include <boost/algorithm/string.hpp>

#include <Resources/ResourceDef.h>
#include <Utils/Logger.h>
#include <Utils/String.h>

Level::Level(WorldManager& worldManager)
	: m_entityFactory(worldManager)
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
	const tinyxml2::XMLElement* objectFileElem = pRoot->FirstChildElement("Objects");

	if(!objectFileElem)
	{
		CORE_ERROR("No Object element defined in " + filename);
		return;
	}

	std::string objectFile = make_string(objectFileElem->GetText());

	if(objectFile.empty())
	{
		CORE_ERROR("No object file defined in: " + filename);
		return;
	}

	// Trim whitespace
	boost::algorithm::trim(objectFile);

	// Load object directory using entity loader
	m_entityFactory.load(objectFile);

	// Load constants....
}

void Level::reload(bool reloadResources, bool reloadEntities)
{
	assert(!m_prevLevelFile.empty());


	if(reloadEntities)
	{
		CORE_LOG("LEVEL", "Removing all entities from manager...");
		m_entityManager->removeAllEntities();
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