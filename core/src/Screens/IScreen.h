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

    virtual bool init() = 0;
    virtual void dispose() = 0;

    virtual void pollInput(const sf::Event&) = 0;
    virtual void update(float) = 0;
    virtual void render() = 0;

    virtual void resize(const sf::Vector2u&) = 0;
};

#endif // SCREEN_H
