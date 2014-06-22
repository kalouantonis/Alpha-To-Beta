#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Screens/IScreen.h>

#include <Graphics/SpriteBatch.h>
#include <Graphics/Camera2D.h>

#include <Screens/GameManager.h>

#include <Entities/Level.h>

class GameScreen: public IScreen
{
public:
    GameScreen(sf::RenderTargetPtr pWindow);
    ~GameScreen();

    // IScreen interface
    bool init() final;
    void pollInput(const sf::Event &event) final;
    void update(float deltaTime) final;
    void render() final;

    void resize(const sf::Vector2u &size) final;

private:
    sf::RenderTargetPtr m_pRenderTarget;

    GameManager m_gameManager;

    SpriteBatch m_spriteBatch;
    Camera2D m_camera;

    Level m_level;
};

#endif // GAMESCREEN_H
