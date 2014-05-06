/*
 * main.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#include <SFML/System/Clock.hpp>
#include <Game.h>

#include <Screens/ScreenManager.h>
#include <Screens/GameScreen.h>
#include <Utils/Logger.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

const int FPS = 60;
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

	game.dispose();

    return EXIT_SUCCESS;
}
