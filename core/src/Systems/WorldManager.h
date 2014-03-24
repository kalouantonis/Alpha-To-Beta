#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <Artemis/World.h>
#include <SFML/System/NonCopyable.hpp>

class WorldManager: public artemis::World, private sf::NonCopyable
{
public:
	WorldManager(): artemis::World() {}
	virtual ~WorldManager() {}

	virtual void initialize() = 0;
	virtual void dispose() = 0;
	virtual void update(float delta);
	virtual void render() = 0;
};

#endif // WORLDMANAGER_H