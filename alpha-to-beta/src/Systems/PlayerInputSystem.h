#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include <Artemis/EntitySystem.h>

//fwd defs
class DynamicBody;

class PlayerInputSystem: public artemis::EntitySystem
{
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	virtual void added(artemis::Entity& e) final;
    virtual void removed(artemis::Entity& e) final;

private:
    virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag) final;
    virtual bool checkProcessing() final;

    bool containsValidEntity();

	DynamicBody* m_pPlayerBody;	
	/**
	 * Store the entity ID, for checking if removed entity matches current entity
	 */
	int m_eid;
};

#endif // PLAYER_INPUT_SYSTEM_H
