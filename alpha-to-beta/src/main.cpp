/*
 * main.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#include <SFML/System/Clock.hpp>
#ifdef _DEBUG
	#include <SFML/Graphics/Font.hpp>
	#include <SFML/Graphics/Text.hpp>

	const char* DEBUG_FONT_FILE = "assets/debug/font.ttf";
#endif

#include <Game.h>

#include <Screens/ScreenManager.h>
#include <Screens/GameScreen.h>
#include <Utils/Logger.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

const int FPS = 30;
const float FRAME_TIME = 1.f / FPS;

int main()
{
#ifndef _DEBUG
    Logger::instance().setLogFile("info.log");
#endif

	Game game;

    game.init("Alpha To Beta", 1024, 667);

    ScreenManager::getInstance().push(
        UScreenPtr(new GameScreen(game.getWindow()))
    );

#ifdef _DEBUG 

	sf::Font debugFont;
	sf::Text debugText;
	if(debugFont.loadFromFile(DEBUG_FONT_FILE))
	{
		debugText.setFont(debugFont);
	}
	else
	{
		CORE_ERROR("Failed to load debug font: " + std::string(DEBUG_FONT_FILE));
	}

#endif

    // Timing
    float timeSinceLastUpdate = 0.f;
    sf::Clock timer;

	while(game.isRunning())
    {
        timeSinceLastUpdate += timer.restart().asSeconds();
        while(timeSinceLastUpdate > FRAME_TIME)
        {
            // Update input
            game.pollInput();

            // Update game
            game.update(FRAME_TIME);

            // Decrease in fixed time intervals
            timeSinceLastUpdate -= FRAME_TIME;
        }

        // Only render once game logic is finished updating
        game.render();
    }


    return EXIT_SUCCESS;
}
