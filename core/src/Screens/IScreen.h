#ifndef SCREEN_H
#define SCREEN_H

#include <memory>

#include <SFML/System/Vector2.hpp>

#include <SFMLPtrDef.h>

namespace sf
{
// Forward declares, only references used
class Event;
}


class IScreen
{
public:
    IScreen(sf::RenderTargetPtr) {}
    virtual ~IScreen() {}

    /**
     * @brief Initialize screen
     * @return false if failed
     */
    virtual bool init() = 0;
    /**
     * @brief Send SFML poll events to screen
     * @param  SFML poll event
     */
    virtual void pollInput(const sf::Event&) = 0;
    /**
     * @brief Update screen
     * 
     * @param deltaTime Time since last update call
     */
    virtual void update(float deltaTime) = 0;
    /**
     * @brief Draw screen contents to screen
     */
    virtual void render() = 0;
    /**
     * @brief Resize screen
     * @param size Size to resize to
     */
    virtual void resize(const sf::Vector2u& size) = 0;
};

#endif // SCREEN_H
