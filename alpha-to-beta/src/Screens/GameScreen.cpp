#include <Screens/GameScreen.h>
#include <Utils/Logger.h>

#include <SFML/Window/Keyboard.hpp>

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
        // Initialize manager
        m_manager.start();

        return true;
    }
    catch(std::runtime_error& e)
    {
       CORE_ERROR(e.what());

       return false;
    }
}

void GameScreen::dispose()
{
    CORE_DEBUG("Stopping GameManager...");
    m_manager.stop();

    CORE_DEBUG("Disposing GameManager...");
    m_manager.dispose();

    CORE_DEBUG("GameScreen disposed...");
}

void GameScreen::pollInput(const sf::Event &event)
{

}

void GameScreen::update(float deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_camera.move(100 * deltaTime, 0);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_camera.move(-100 * deltaTime, 0);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_camera.move(0, 100 * deltaTime);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_camera.move(0, -100 * deltaTime);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        m_camera.rotate(-10.f * deltaTime);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_camera.rotate(10.f * deltaTime);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        m_camera.zoom(1.1f);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        m_camera.zoom(0.9f);


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
