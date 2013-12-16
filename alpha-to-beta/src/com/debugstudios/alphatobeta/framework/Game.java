/*
 * This file is part of LibGDXTest.
 *
 * LibGDXTest is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibGDXTest is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibGDXTest.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.debugstudios.alphatobeta.framework;

import com.badlogic.gdx.*;
import com.badlogic.gdx.assets.AssetManager;
import com.debugstudios.alphatobeta.framework.screens.GameScreen;

public abstract class Game implements ApplicationListener
{
    GameScreen screen;

    // Screen assets can be loaded here
    AssetManager assetManager;

    private static int FPS = 60;
    // Time for each frame
    private static float FRAME_TIME = 1.f / (float)FPS;

    public Game()
    {
    }

    @Override
    public void create()
    {
        assetManager = new AssetManager();

        screen = getStartScreen();
    }

    @Override
    public void resume()
    {
        screen.resume();
    }

    @Override
    public void pause()
    {
        screen.pause();
    }

    @Override
    public void resize(int width, int height)
    {
        screen.resize(width, height);
    }

    @Override
    public void render()
    {
        /*timeSinceLastFrame += Gdx.graphics.getDeltaTime();

        FRAME_TIME = 1.f / (int)Gdx.graphics.getFramesPerSecond();

        if(timeSinceLastFrame >= FRAME_TIME)
        {
            // Handle input
            screen.handleInput();

            // Update screen
            screen.update(FRAME_TIME);

            timeSinceLastFrame -= FRAME_TIME;
        }*/

        screen.handleInput();

        float deltaTime = Gdx.graphics.getDeltaTime();

        // TODO: Check device frame rate
        if(deltaTime > 0.032f)
            deltaTime = 0.032f;

        screen.update(deltaTime);

        screen.draw();
    }


    @Override
    public void dispose()
    {
        screen.dispose();
        assetManager.dispose();
    }

    public AssetManager getAssetManager()
    {
        return assetManager;
    }

    public void setScreen(GameScreen newScreen)
    {
        if(newScreen == null)
            throw new IllegalArgumentException("Screen must not be null");

        this.screen.pause();
        this.screen.dispose();

        newScreen.resume();
        newScreen.update(0);

        screen = newScreen;
    }

    public abstract GameScreen getStartScreen();

    public GameScreen getCurrentScreen()
    {
        return screen;
    }
}
