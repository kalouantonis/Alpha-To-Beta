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
#include <SFML/System/NonCopyable.hpp>

class IEventManager;
typedef std::shared_ptr<IEventManager> EventManagerPtr;

/**
 * Main game class
 */
class Game: private sf::NonCopyable
{
public:
	Game();
	virtual ~Game();

    /**
     * @brief Initialize game engine
     * 
     * @param title Window title of game
     * @param width Window width
     * @param height Window height
     * @param fullscreen Set window to fullscreen. Set to false by default
     */
	void init(const char* title, int width, int height, bool fullscreen = false);

    /**
     * @brief Poll and dispatch input events
     */
    void pollInput();
    /**
     * @brief Update engine
     * 
     * @param dt Time since last update
     */
    void update(float dt);
    /**
     * @brief Render engine contents
     */
    void render();

    /**
     * @brief Get current window pointer
     */
    sf::RenderTargetPtr getWindow() const { return m_pWindow; }

    /**
     * @brief Is game engine running?
     * @return true if running
     */
	bool isRunning() const
	{
		return m_bRunning;
	}

private:
	bool m_bRunning;
	/** True if window is currently focused */
	bool m_bInFocus;
    sf::RenderWindowPtr m_pWindow;

    EventManagerPtr m_pEventManager;
};

#endif /* GAME_H_ */
