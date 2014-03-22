#ifndef XMLOADER_H
#define XMLOADER_H

#include <tinyxml2.h>
#include <string>

class XMLoader
{
public:
    static bool loadFile(const char* filename);
    /**
     * @brief Gets root from loaded document
     * @return
     */
    static tinyxml2::XMLElement* getRoot();
    /**
     * @brief Loads and gets the root of the document
     * @param filename
     * @return
     */
    static tinyxml2::XMLElement* loadAndGetRoot(const char* filename);

    // Maybe get second error string too
    static std::string getLastError() { return m_doc.GetErrorStr1(); } 
    static bool hasErrorOccured() { return m_doc.Error(); }

private:
    static tinyxml2::XMLDocument m_doc;
};

#endif // XMLOADER_H
