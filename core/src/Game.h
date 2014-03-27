/*
 * Game.h
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#ifndef GAME_H_
#define GAME_H_

#include <SFMLPtrDef.h>
#include <string>
// Needed for base class info
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
public:
	Game();
	virtual ~Game();

	void init(const char* title, int width, int height, bool fullscreen = false);

	virtual void pollInput();
	virtual void update(float dt);
	virtual void render();

	virtual void dispose();

    sf::RenderTargetPtr getWindow() const { return m_pWindow; }

	bool isRunning() const
	{
		return m_bRunning;
	}

private:
	bool m_bRunning;
	/** True if window is currently focused */
	bool m_bInFocus;
    sf::RenderWindowPtr m_pWindow;
};

#endif /* GAME_H_ */
