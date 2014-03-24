#include <Systems/WorldManager.h>

void WorldManager::update(float delta)
{
	this->loopStart();
	this->setDelta(delta);
}