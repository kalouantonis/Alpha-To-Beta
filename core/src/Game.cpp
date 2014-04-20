/*
 * Game.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

#include <Game.h>
#include <Utils/Logger.h>
#include <Utils/FileSystem.h>
#include <Screens/ScreenManager.h>


Game::Game()
	: m_bRunning(false)
    , m_bInFocus(false)
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    // TODO: Load context settings from game settings file
    // Disable resizing for now
    sf::Uint32 winFlags = sf::Style::Close;

    if(fullscreen)
        winFlags |= sf::Style::Fullscreen;

    m_pWindow.reset(new sf::RenderWindow(sf::VideoMode(width, height), title, winFlags),
                   // Define custom de-allocator when all references are destroyed
                   [](sf::RenderWindow* p) {
        CORE_INFO("Closing window...");
        p->close();
        CORE_DEBUG("Deleting window...");
        delete p;
    });

    CORE_INFO("Window created...");

	// Get context settings
    const sf::ContextSettings& settings = m_pWindow->getSettings();
    CORE_LOG("OGL", "Depth Bits: " + std::to_string(settings.depthBits));
    CORE_LOG("OGL", "Stencil Bits: " + std::to_string(settings.stencilBits));
    CORE_LOG("OGL", "Anti-aliasing level: " + std::to_string(settings.antialiasingLevel));
    CORE_LOG("OGL", "OpenGL Version: " + std::to_string(settings.majorVersion)
            + '.' + std::to_string(settings.minorVersion));

    // Seed randomizer
    srand((unsigned int) time(NULL));
    CORE_DEBUG("Randomizer seeded...");

    CORE_INFO("Current working directory: " + fs::currentWorkingDir());

	m_bRunning = true;
	// Set to true now, for some reason, windows doesnt catch the 
	// focused event when the game is loaded
	m_bInFocus = true;
}

void Game::render()
{
    if(m_bInFocus)
    {
    	// Clear screen
        m_pWindow->clear();

        ScreenManager::getInstance().render();

        // Flip screen buffers
        m_pWindow->display();
    }
}

void Game::pollInput()
{
    // TODO: Allow game to receive events, such as close requests and stuff
	sf::Event event;

    while(m_pWindow->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			m_bRunning = false;
			break;
        case sf::Event::LostFocus:
            CORE_LOG("EVENT", "Window lost focus");
            m_bInFocus = false;
            break;
        case sf::Event::GainedFocus:
            CORE_LOG("EVENT", "Window gained focus");
            m_bInFocus = true;
            break;
        case sf::Event::Resized:
            ScreenManager::getInstance().resize(sf::Vector2u(event.size.width, event.size.height));
            break;
        default:
            ScreenManager::getInstance().pollInput(event);
		}
	}
}

void Game::update(float dt)
{
    if(m_bInFocus)
        ScreenManager::getInstance().update(dt);

}

void Game::dispose()
{
    CORE_DEBUG("Disposing screens...");
    ScreenManager::getInstance().dispose();
}
