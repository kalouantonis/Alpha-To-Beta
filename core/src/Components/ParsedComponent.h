#ifndef PARSED_COMPONENT_H
#define PARSED_COMPONENT_H

#include <Artemis/Component.h>

#include <memory>

namespace tinyxml2
{
class XMLElement;
}

class ParsedComponent: public artemis::Component
{
public:
	virtual ~ParsedComponent() {}

    /**
     * @brief Load component from XML element
     * @details Each component is tasked with parsing its own XML element
     * 
     * @param pElement Pointer to XML element
     * @return True if loading success
     */
	virtual bool load(const tinyxml2::XMLElement* pElement) = 0;
    /**
     * @brief Convert component data to XML element
     */
	virtual tinyxml2::XMLElement* toXML() const { return nullptr; }
    /**
     * @brief Get the name of the component
     */
	virtual const char* getName() const = 0;
};

typedef std::shared_ptr<ParsedComponent> ComponentPtr;

#endif // PARSED_COMPONENT_H