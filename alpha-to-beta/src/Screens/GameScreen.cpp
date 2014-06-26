#include <Screens/GameScreen.h>
#include <Utils/Logger.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <Artemis/SystemManager.h>

GameScreen::GameScreen(sf::RenderTargetPtr pWindow)
    : IScreen(pWindow)
    , m_pRenderTarget(pWindow)
    , m_spriteBatch(pWindow)
    , m_camera(pWindow)
{
}

bool GameScreen::init()
{
    m_gameManager.init();
    m_gameManager.initPhysics(sf::Vector2f(0, 9.81f), sf::Vector2f(70, 70));

#ifdef _DEBUG
    m_gameManager.initPhysicsRenderer(m_pRenderTarget);
#endif
    m_gameManager.initRenderer(m_spriteBatch, m_camera);
    if(!m_gameManager.initLua())
        return false;

    m_gameManager.registerComponents();
    m_gameManager.registerScriptEvents();

    m_gameManager.start();

	CORE_DEBUG("Loading entities...");
	m_level.load("assets/levels/level1.xml");

	CORE_DEBUG("Initialization complete.");

	return true;
}

GameScreen::~GameScreen()
{
    m_gameManager.unregisterComponents();
    m_gameManager.unregisterScriptEvents();

    m_gameManager.destroy();

    m_gameManager.destroyLua();
#ifdef _DEBUG
    m_gameManager.destroyPhysicsRenderer();
#endif
    m_gameManager.destroyPhysics();

    CORE_DEBUG("GameScreen disposed...");
}

void GameScreen::pollInput(const sf::Event &event)
{
	if(event.type == sf::Event::MouseWheelMoved)
	{
		m_camera.zoom(event.mouseWheel.delta != 1 ? 1.1f : 0.9f);
	}
}

void GameScreen::update(float deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        m_level.reload();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_camera.move(-0.05f, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_camera.move(0.05f, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_camera.move(0, -0.05f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_camera.move(0, 0.05f);
    }

    m_gameManager.update(deltaTime);
}

void GameScreen::render()
{
    m_gameManager.render();
}

void GameScreen::resize(const sf::Vector2u &size)
{
    // m_camera.resize(size);
}
