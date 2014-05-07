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
    case sf::Event::MouseButtonReleased:
        inputProcessor->mouseReleased(event.mouseButton);
        break;
    case sf::Event::MouseWheelMoved:
        inputProcessor->mouseScrolled(event.mouseWheel);
	default:
		break;
	}
}


//Locator::Ptr owned_processor(InputProcessor *p)
//{
//    // Void deleter
//    return Locator::Ptr(p, [](InputProcessor* p) {});
//}
