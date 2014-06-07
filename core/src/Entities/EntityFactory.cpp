#include <Entities/EntityFactory.h>

#include <Utils/Logger.h>
#include <Resources/XMLoader.h>

// Component includes
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>
#include <Components/PlayerInput.h>
#include <Components/CameraFollower.h>

#include <Artemis/Entity.h>
#include <Artemis/TagManager.h>

#include <Entities/WorldLocator.h>

#include <boost/filesystem.hpp>

using namespace boost;


EntityFactory::EntityFactory()
{
    m_componentFactory.declare<Transform>(Transform::g_name);
    m_componentFactory.declare<Renderable>(Renderable::g_name);
    m_componentFactory.declare<DynamicBody>(DynamicBody::g_name);
    m_componentFactory.declare<JumpBehaviour>(JumpBehaviour::g_name);
    m_componentFactory.declare<PlayerInput>(PlayerInput::g_name);
    m_componentFactory.declare<CameraFollower>(CameraFollower::g_name);
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
                    // FIXME: Recurse is broken
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
