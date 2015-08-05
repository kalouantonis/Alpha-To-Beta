#include <Entities/Utils.h>

#include <Entities/WorldLocator.h>

std::string getGroupName(artemis::Entity& e)
{
	return WorldLocator::getObject()->getGroupManager()->getGroupOf(e);
}