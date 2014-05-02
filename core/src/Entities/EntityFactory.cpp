#include <Entities/EntityFactory.h>

#include <Utils/Logger.h>
#include <Resources/XMLoader.h>

// Component includes
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/Physics.h>

#include <Artemis/Entity.h>
#include <Artemis/TagManager.h>

#include <boost/filesystem.hpp>

using namespace boost;


EntityFactory::EntityFactory(WorldManager& worldManager)
    : m_worldManager(worldManager)
{
    m_componentFactory.declare<Transform>(Transform::g_name);
    m_componentFactory.declare<Renderable>(Renderable::g_name);
    // m_componentFactory.declare<Physics>(Physics::g_name);
}

EntityFactory::~EntityFactory()
{
    m_componentFactory.clear();
}

void EntityFactory::invalidateEntity(artemis::Entity& entity)
{
    // Set as invalid ID so as to be able to validate success later
    entity.setUniqueId(INVALID_ENTITY);
    // Remove from world
    entity.remove();
}

artemis::Entity& EntityFactory::loadFromFile(const std::string &filename)
{
    // Get root element of xml file
    const tinyxml2::XMLElement* pRoot = m_xmlLoader.loadAndGetRoot(filename.c_str());

    // Request new empty entity from manager
    artemis::Entity& entity = m_worldManager.createEntity();

    // check if root exists
    if(!pRoot)
    {
        std::string errmsg = "Failed to load xml resource: " + filename;

        if(m_xmlLoader.hasErrorOccured())
        {
            errmsg += "\n\tDetails: " + m_xmlLoader.getLastError();
        }

        CORE_ERROR(errmsg);

        invalidateEntity(entity);
        return entity;
    }

    if(pRoot->NoChildren())
    {
        CORE_WARNING("No children in xml: " + filename
                   + ", will not load entity.");

        invalidateEntity(entity);
        return entity;
    }

    // Try and get tag attribute from xml entity
    const char* tag = pRoot->Attribute("tag");


    if(tag != NULL)
    {
        if(!m_worldManager.getTagManager()->isSubscribed(tag))
            m_worldManager.getTagManager()->subscribe(tag, entity);
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

    return entity;
}

void EntityFactory::load(const std::string &path, bool recurse)
{
    // convert to file system path
    filesystem::path fsPath(path);

    try
    {
        // Check file existance
        if(filesystem::exists(fsPath))
        {
            // Only use xml files
            if((filesystem::is_regular_file(fsPath)) &&
                (fsPath.extension().generic_string() == ".xml"))
            {
                loadFromFile(path);
            }
            else if(filesystem::is_directory(path))
            {
                // File containers
                std::vector<filesystem::path> fileVec;

                if(recurse)
                {
                    // Get recursive
                    std::copy(
                        filesystem::recursive_directory_iterator(fsPath),
                        filesystem::recursive_directory_iterator(),
                        std::back_inserter(fileVec) // Insert in to new file vector
                    );
                }
                else
                {
                    // FIXME: Recurse if broken
                    // Ignore folders
                    std::copy(
                        filesystem::directory_iterator(fsPath),
                        filesystem::directory_iterator(),
                        std::back_inserter(fileVec)
                    );
                }

                for(const auto& file : fileVec)
                {
                    if((filesystem::is_regular_file(file)) &&          // Just a normal file
                        (file.extension().generic_string() == ".xml"))  // Has XML extension
                    {
                        loadFromFile(file.string());
                    }
                }
            }
            else
            {
                CORE_WARNING(path + ": No directory or file with \".xml\" extension found");
            }
        }
        else
        {
            CORE_WARNING(path + ": Does not exist, ignoring...");
        }
    }
    catch(const filesystem::filesystem_error& ex)
    {
        CORE_FATAL("File system error: " + std::string(ex.what()));
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
