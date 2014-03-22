#include <Entities/EntityFactory.h>

#include <Utils/Logger.h>
#include <Resources/XMLoader.h>

// Component includes
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/Physics.h>



EntityFactory::EntityFactory(EntityManagerPtr pEntityManager)
    : m_pEntityManager(pEntityManager)
{
    m_componentFactory.declare<Transform>(Transform::family());
    m_componentFactory.declare<Renderable>(Renderable::family());
    m_componentFactory.declare<Physics>(Physics::family());
}

void EntityFactory::loadEntity(const std::string &filename)
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

ComponentPtr EntityFactory::createComponent(const tinyxml2::XMLElement *pElement)
{
    // Get element value
    const char* componentName = pElement->Value();

    //ComponentPtr pComponent(m_componentFactory.create())

    return ComponentPtr();
}
