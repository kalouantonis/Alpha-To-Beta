#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Screens/IScreen.h>

#include <Graphics/SpriteBatch.h>
#include <Graphics/Camera2D.h>

#include <Entities/Level.h>

#include <Artemis/World.h>

// fwd decls
class RenderSystem;
class PhysicsSystem;
class PlayerInputSystem;
class Box2DRenderer;
class JumpListener;
class CameraFollowingSystem;
class ScriptSystem;

class GameScreen: public IScreen
{
public:
    GameScreen(sf::RenderTargetPtr window);
    ~GameScreen();

    // IScreen interface
    bool init() final;
    void pollInput(const sf::Event &event) final;
    void update(float deltaTime) final;
    void render() final;

    void resize(const sf::Vector2u &size) final;

private:
    // GameManager m_manager;
    std::shared_ptr<artemis::World> m_world;

    SpriteBatch m_spriteBatch;
    Camera2D m_camera;

    RenderSystem* m_pRenderSystem;
    PhysicsSystem* m_pPhysicsSystem;
    PlayerInputSystem* m_pInputSystem;
    CameraFollowingSystem* m_pCameraSystem;
    ScriptSystem* m_pScriptSystem;

    std::unique_ptr<JumpListener> m_pJumpListener;

    std::shared_ptr<Box2DRenderer> m_pB2Renderer;

    Level m_level;
};

#endif // GAMESCREEN_H
