#ifndef PARSEDCOMPONENT_H
#define PARSEDCOMPONENT_H

#include <entityx/Entity.h>

namespace tinyxml2
{
class XMLElement;
}

/**
 * @brief Component that can be loaded from XML elements
 */
template<class CompType>
struct ParsedComponent: public entityx::Component<CompType>
{
public:
	/**
	 * @brief Destructor for polymorphic class
	 */
    virtual ~ParsedComponent() {}

    /**
     * @brief Load component from XML data
     * 
     * @param XML element data
     * @return true if success, false if failed
     */
    virtual bool load(const tinyxml2::XMLElement* pElement) = 0;
};

//typedef std::shared_ptr<ParsedComponent> ComponentPtr;

#endif // PARSEDCOMPONENT_H
