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

	virtual bool load(const tinyxml2::XMLElement* pElement) = 0;
};

typedef std::shared_ptr<ParsedComponent> ComponentPtr;

#endif // PARSED_COMPONENT_H