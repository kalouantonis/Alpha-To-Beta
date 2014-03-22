#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Screens/IScreen.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/Camera2D.h>
#include <Systems/GameManager.h>

class GameScreen: public IScreen
{
public:
    GameScreen(sf::RenderTargetPtr window);

    // IScreen interface
    bool init() final;
    void dispose() final;

    void pollInput(const sf::Event &event) final;
    void update(float deltaTime) final;
    void render() final;

    void resize(const sf::Vector2u &size) final;

private:
    SpriteBatch m_spriteBatch;
    Camera2D m_camera;
    GameManager m_manager;
};

#endif // GAMESCREEN_H
