#include <Screens/GameScreen.h>
#include <Utils/Logger.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <Resources/ResourceDef.h>

GameScreen::GameScreen(sf::RenderTargetPtr window)
    : IScreen(window)
    , m_spriteBatch(window, 20)
    , m_camera(window)
    , m_manager(m_spriteBatch)
{
}


bool GameScreen::init()
{

    try
    {
        TextureLocator::provide(TextureLocator::Ptr(new TextureHolder()));
        // Initialize manager
        m_manager.initialize();

        return true;
    }
    catch(std::runtime_error& e)
    {
       CORE_ERROR(e.what());

       return false;
    }
}

GameScreen::~GameScreen()
{
    // CORE_DEBUG("Disposing GameManager...");
    // m_manager.dispose();
    
    CORE_DEBUG("Disposing textures...");
    TextureLocator::getObject()->clear();

    CORE_DEBUG("Disposing TextureLocator...");
    TextureLocator::remove();

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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_camera.move(100 * deltaTime, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_camera.move(-100 * deltaTime, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_camera.move(0, 100 * deltaTime);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_camera.move(0, -100 * deltaTime);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        m_camera.rotate(-10.f * deltaTime);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_camera.rotate(10.f * deltaTime);
    
    m_manager.update(deltaTime);
}

void GameScreen::render()
{
    m_manager.render();
}

void GameScreen::resize(const sf::Vector2u &size)
{
    m_camera.resize(size);
}
