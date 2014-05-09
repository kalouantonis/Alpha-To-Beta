#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>

#include <Screens/IScreen.h>

namespace sf
{
class Event;
}

typedef std::unique_ptr<IScreen> UScreenPtr;


class ScreenManager
{
public:
    static ScreenManager& getInstance()
    {
        static ScreenManager instance;
        return instance;
    }

    void push(UScreenPtr pScreen);
    void change(UScreenPtr pScreen);
    void pop();

    void update(float deltaTime);
    void render();
    void pollInput(const sf::Event& event);

    void resize(const sf::Vector2u& size);

private:
    ScreenManager(): m_screenStack() {}
    ScreenManager(const ScreenManager&) {}
    void operator=(const ScreenManager&) {}

    std::vector<UScreenPtr> m_screenStack;
};


#endif // SCREENMANAGER_H
