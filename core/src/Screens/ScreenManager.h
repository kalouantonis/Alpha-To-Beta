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

    /**
     * @brief Add new screen to manager and transfer ownership
     * @param pScreen Screen pointer to add
     */
    void push(UScreenPtr pScreen);
    /**
     * @brief Change current screen.
     * @details New screen will be pushed to the top of the stack
     * while the old one remains below, but will not be updated
     * 
     * @param pScreen Screen pointer to add
     */
    void change(UScreenPtr pScreen);
    /**
     * @brief Remove item off top of stack
     */
    void pop();

    /**
     * @brief Clear all screens
     */
    void clear();

    /**
     * @brief Update current screen
     * 
     * @param deltaTime Time since last update
     */
    void update(float deltaTime);
    /**
     * @brief Render screen contents
     */
    void render();
    /**
     * @brief Dispatch polled input events
     * @param event Events
     */
    void pollInput(const sf::Event& event);
    /**
     * @brief Resize screen 
     * 
     * @param size Screen resize dimensions
     */
    void resize(const sf::Vector2u& size);

private:
    ScreenManager(): m_screenStack() {}
    ScreenManager(const ScreenManager&) {}
    void operator=(const ScreenManager&) {}

    std::vector<UScreenPtr> m_screenStack;
};


#endif // SCREENMANAGER_H
