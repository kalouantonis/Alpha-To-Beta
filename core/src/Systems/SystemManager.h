#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <entityx/Manager.h>

class SystemManager: public entityx::Manager
{
public:
	// Update called manually
	virtual void update(float dt) = 0;
	virtual void render() = 0;

	virtual void dispose() = 0;

private:
	// Disable auto-running of the manager
	virtual void run() final {}
	virtual void step(float dt) final {}
};

#endif // SYSTEM_MANAGER_H