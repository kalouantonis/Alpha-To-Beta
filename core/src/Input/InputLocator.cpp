#include <Input/InputLocator.h>

void InputLocator::dispatchEvent(const sf::Event& event)
{
	Ptr inputProcessor = getObject();

	if(inputProcessor == nullptr)
		return;

	switch(event.type)
	{
	case sf::Event::KeyPressed:
		inputProcessor->keyPressed(event.key);
		break;
	case sf::Event::KeyReleased:
		inputProcessor->keyReleased(event.key);
		break;
	case sf::Event::MouseButtonPressed:
		inputProcessor->mousePressed(event.mouseButton);
		break;
	default:
		break;
	}
}