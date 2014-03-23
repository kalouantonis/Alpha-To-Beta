#include <Entities/EntityFactory.h>

#include <Utils/Logger.h>
#include <Resources/XMLoader.h>

// Component includes
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/Physics.h>

#include <boost/filesystem.hpp>

using namespace boost;


EntityFactory::EntityFactory(EntityManagerPtr pEntityManager)
    : m_pEntityManager(pEntityManager)
{
    m_componentFactory.declare<Transform>(Transform::family());
    m_componentFactory.declare<Renderable>(Renderable::family());
    m_componentFactory.declare<Physics>(Physics::family());
}

void EntityFactory::loadFromFile(const std::string &filename)
{
    // Get root element of xml file
    const tinyxml2::XMLElement* pRoot = m_xmlLoader.loadAndGetRoot(filename.c_str());

    // check if root exists
    if(!pRoot)
    {
        std::string errmsg = "Failed to load xml resource: " + filename;

        if(m_xmlLoader.hasErrorOccured())
            errmsg += m_xmlLoader.getLastError();

        CORE_ERROR(errmsg);
        return;
    }

    if(pRoot->NoChildren())
    {
        CORE_WARNING("No children in xml: " + filename
                   + ", will not load entity.");

        // exit
        return;
    }

    // Request new empty entity from manager
    entityx::Entity entity = m_pEntityManager->create();


    // Go through each element (component def in this case)
    for(auto pElem = pRoot->FirstChildElement(); pElem != NULL;
        pElem = pElem->NextSiblingElement())
    {
        ComponentPtr pComponent(createComponent(pElem));

        if(pComponent != nullptr)
        {
            // add component in to entity
            entity.assign(pComponent);
        }
        else
        {
            CORE_WARNING("Failed to load component from " + filename
                         + ", it will be ignored");
        }
    }

    CORE_DEBUG("Created entity from " + filename);
}

void EntityFactory::loadFromDirectory(const std::string &path, bool recurse)
{
    // convert to file system path
    filesystem::path fsPath(path);

    try
    {
        if(filesystem::exists(fsPath))
        {
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
                        std::back_inserter(fileVec)
                    );
                }
                else
                {
                    std::copy(
                        filesystem::directory_iterator(fsPath),
                        filesystem::directory_iterator(),
                        std::back_inserter(fileVec)
                    );
                }

                for(auto file : fileVec)
                {
                    if((!filesystem::is_regular_file(file)) &&          // Just a normal file
                        (file.extension().generic_string() == ".xml"))  // Has XML extension
                    {
                        loadFromFile(fsPath.native() + file.filename().native());
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

ComponentPtr EntityFactory::createComponent(const tinyxml2::XMLElement *pElement)
{
    // Get element value
    const char* componentName = pElement->Value();

    //ComponentPtr pComponent(m_componentFactory.create())
    //pComponent->load(pElement);

    return ComponentPtr();
}
