#include <Entities/EntityFactory.h>

#include <Utils/Logger.h>
#include <Utils/String.h>
#include <Resources/XMLoader.h>

// Component includes
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/BaseAnimation.h>
#include <Components/DynamicBody.h>
#include <Components/PlayerInput.h>
#include <Components/CameraFollower.h>
#include <Components/BaseScriptComponent.h>

#include <Artemis/Entity.h>
#include <Artemis/TagManager.h>

#include <Entities/WorldLocator.h>

//#include <boost/filesystem.hpp>
#include <tinydir.h>

//using namespace boost;

EntityFactory::EntityFactory()
{
    m_componentFactory.declare<Transform>(Transform::g_name);
    m_componentFactory.declare<Renderable>(Renderable::g_name);
	m_componentFactory.declare<BaseAnimation>(BaseAnimation::g_name);
    m_componentFactory.declare<DynamicBody>(DynamicBody::g_name);
    m_componentFactory.declare<PlayerInput>(PlayerInput::g_name);
    m_componentFactory.declare<CameraFollower>(CameraFollower::g_name);
    m_componentFactory.declare<BaseScriptComponent>(BaseScriptComponent::g_name);
}

EntityFactory::~EntityFactory()
{
    m_componentFactory.clear();
}

EntityFactory& EntityFactory::get()
{
    static EntityFactory instance;
    return instance;
}

bool EntityFactory::loadFromFile(const std::string &filename)
{
    // Create new entity
    return loadFromFile(filename, WorldLocator::getObject()->createEntity());
}

bool EntityFactory::loadFromFile(const std::string& filename, artemis::Entity& entity)
{
     // Get root element of xml file
    const tinyxml2::XMLElement* pRoot = m_xmlLoader.loadAndGetRoot(filename.c_str());

    // check if root exists
    if(!pRoot)
    {
        std::string errmsg = "Failed to load xml resource: " + filename;

        if(m_xmlLoader.hasErrorOccured())
        {
            errmsg += "\n\tDetails: " + m_xmlLoader.getLastError();
        }

        CORE_ERROR(errmsg);

        return false;
    }

    if(pRoot->NoChildren())
    {
        CORE_WARNING("No children in xml: " + filename
                   + ", will not load entity.");
        return false;
    }

//    // Try and get tag attribute from xml entity
//    const char* tag = pRoot->Attribute("tag");
//
//
//    if(tag != NULL)
//    {
//        if(!m_worldManager.getTagManager()->isSubscribed(tag))
//            m_worldManager.getTagManager()->subscribe(tag, entity);
//    }

	std::string group = make_string(pRoot->Attribute("group"));

	if(!group.empty())
	{
		entity.setGroup(group);
	}



    // Go through each element (component def in this case)
    for(auto pElem = pRoot->FirstChildElement(); pElem != NULL;
        pElem = pElem->NextSiblingElement())
    {
        ParsedComponent* pComponent = createComponent(pElem);

        if(pComponent != nullptr)
        {
            // add component to entity
            entity.addComponent(pComponent);
        }
        else
        {
            CORE_ERROR("Failed to load component from " + filename);
        }
    }

    if(entity.getComponents().isEmpty())
    {
        CORE_WARNING("No components in entity, removing...");
        entity.remove();
    }
    else
    {
        CORE_DEBUG("Created entity from " + filename);
        entity.refresh();
    }

    return true;
}

void EntityFactory::load(const std::string &path, bool recurse)
{
	tinydir_dir dir;

	if(tinydir_open(&dir, path.c_str()) == -1)
	{
		// Error
		CORE_ERROR("Failed to open directory: " + path);

		tinydir_close(&dir);
		return;
	}

	while(dir.has_next)
	{
		tinydir_file file;

		if(tinydir_readfile(&dir, &file) == -1)
		{
			CORE_ERROR("Failed to load file: " + std::string(file.path));
			continue;
		}

		if(file.is_dir && recurse)
		{
			// TODO: Check if this works
			load(file.path, true);
		}
		else 
		{
			loadFromFile(file.path);
		}

		tinydir_next(&dir);
	}
}

ParsedComponent* EntityFactory::createComponent(const tinyxml2::XMLElement *pElement)
{
    // Get element value
    const char* componentName = pElement->Value();

    // Create component
    ParsedComponent* pComponent = m_componentFactory.create(componentName);

    // initialize the component if we found one
    if(pComponent != nullptr)
    {
        if(!pComponent->load(pElement))
        {
            CORE_ERROR("Component failed to initialize: " + std::string(componentName));
            // Destroy un-used component
            delete pComponent;

            return nullptr;
        }
    }
    else
    {
        CORE_ERROR("Couldn't find a component named: " + std::string(componentName));
        return nullptr;
    }

    return pComponent;
}
