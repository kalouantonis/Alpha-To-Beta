#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>


namespace sf
{
class Event;
}

class IScreen;

/**
 * @brief Used for unique_ptr disposal, should not be used externally
 * 
 * @param p Screen to be deleted
 */
inline void _deleter(IScreen* p);
typedef std::unique_ptr<IScreen, std::function<void(IScreen*)>> UScreenPtr;

/**
 * @brief Create a new unique pointer from a screen ptr
 * 
 * @param screen Pointer to screen instance
 * @return Unique pointer with assigned destructor 
 */
UScreenPtr make_screen(IScreen* screen);

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

    void dispose();

private:
    ScreenManager(): m_screenStack() {}
    ScreenManager(const ScreenManager&) {}
    void operator=(const ScreenManager&) {}

    // TODO: Use Unique PTr's
    std::vector<UScreenPtr> m_screenStack;
};


#endif // SCREENMANAGER_H
