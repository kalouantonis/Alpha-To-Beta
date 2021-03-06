#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <SFML/Window/Event.hpp>

/**
 * @brief Classes that want to receive input events
 * @details Purelly virtual, because it may be used in multiple inheritance
 * 
 * @param key [description]
 */
class InputProcessor
{
public:
	virtual void keyPressed(sf::Event::KeyEvent key) = 0;
	virtual void keyReleased(sf::Event::KeyEvent key) = 0;	

	virtual void mousePressed(sf::Event::MouseButtonEvent event) = 0;
	virtual void mouseReleased(sf::Event::MouseButtonEvent event) = 0;
	virtual void mouseScrolled(sf::Event::MouseWheelEvent scroll) = 0;
};

#endif // INPUT_PROCESSOR_H
