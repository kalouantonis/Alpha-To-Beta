#ifndef XMLOADER_H
#define XMLOADER_H

#include <tinyxml2.h>
#include <string>

class XMLoader
{
public:
    bool loadFile(const char* filename);
    /**
     * @brief Gets root from loaded document
     * @return
     */
    tinyxml2::XMLElement* getRoot();
    /**
     * @brief Loads and gets the root of the document
     * @param filename
     * @return
     */
    tinyxml2::XMLElement* loadAndGetRoot(const char* filename);

    // Maybe get second error string too
    std::string getLastError() const { return m_doc.GetErrorStr1(); } 
    bool hasErrorOccured() const { return m_doc.Error(); }

private:
    tinyxml2::XMLDocument m_doc;
};

#endif // XMLOADER_H
