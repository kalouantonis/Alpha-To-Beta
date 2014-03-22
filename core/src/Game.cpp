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
#include <Screens/ScreenManager.h>


Game::Game()
	: m_bRunning(false)
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height)
{
    //m_window.create(sf::VideoMode(width, height), title);
    m_pWindow.reset(new sf::RenderWindow(sf::VideoMode(width, height), title),
                   // Define custom de-allocator when all references are destroyed
                   [](sf::RenderWindow* p) {
        CORE_INFO("Closing window...");
        p->close();
        CORE_DEBUG("Deleting window...");
        delete p;
    });

    CORE_INFO("Window created...");

	// Get context settings
    sf::ContextSettings settings = m_pWindow->getSettings();
    CORE_LOG("OGL", "Depth Bits: " + std::to_string(settings.depthBits));
    CORE_LOG("OGL", "Stencil Bits: " + std::to_string(settings.stencilBits));
    CORE_LOG("OGL", "Anti-aliasing level: " + std::to_string(settings.antialiasingLevel));
    CORE_LOG("OGL", "OpenGL Version: " + std::to_string(settings.majorVersion)
            + '.' + std::to_string(settings.minorVersion));

    // Seed randomizer
    srand(time(NULL));
    CORE_DEBUG("Randomizer seeded...");

	m_bRunning = true;
}

void Game::render()
{
	// Clear screen
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_pWindow->clear();

    ScreenManager::getInstance().render();

    // Flip screen buffers
    m_pWindow->display();
}

void Game::pollInput()
{
	sf::Event event;

    while(m_pWindow->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			m_bRunning = false;
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

    ScreenManager::getInstance().update(dt);
}

void Game::dispose()
{
    CORE_DEBUG("Disposing screens...");
    ScreenManager::getInstance().dispose();
}
