#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include <Artemis/EntitySystem.h>
#include <Input/InputProcessor.h>

//fwd defs
class DynamicBody;

class PlayerInputSystem: public artemis::EntitySystem, public InputProcessor
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

    // InputProcessor interface
private:
    void keyPressed(sf::Event::KeyEvent key);
    void keyReleased(sf::Event::KeyEvent key);
    void mousePressed(sf::Event::MouseButtonEvent event) {}
    void mouseReleased(sf::Event::MouseButtonEvent event) {}
    void mouseScrolled(sf::Event::MouseWheelEvent scroll) {}
};

#endif // PLAYER_INPUT_SYSTEM_H
