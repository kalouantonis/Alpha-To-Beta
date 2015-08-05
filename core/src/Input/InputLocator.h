#ifndef INPUT_LOCATOR_H
#define INPUT_LOCATOR_H

#include <Resources/Locator.h>
#include <Input/InputProcessor.h>

class InputLocator: public Locator<InputProcessor>
{
	// Game class is the only one that can call private methods
	// Remember kids, only friends have access to your privates...
	friend class Game;

private:
    /**
     * @brief Dispatch SFML event to listening input processor
     * 
     * @param event Event to extract and dispatch
     */
	static void dispatchEvent(const sf::Event& event);
};

#endif // INPUT_LOCATOR_H
