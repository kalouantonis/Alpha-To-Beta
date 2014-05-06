#include "XMLoader.h"

bool XMLoader::loadFile(const char *filename)
{
    m_doc.LoadFile(filename);

    return !m_doc.Error();
}

tinyxml2::XMLElement *XMLoader::getRoot()
{
    return m_doc.RootElement();
}

tinyxml2::XMLElement *XMLoader::loadAndGetRoot(const char *filename)
{
    if(!loadFile(filename))  // failed to load
        // Return NULL because tinyxml will do so too
        return NULL;

    return getRoot();
}
