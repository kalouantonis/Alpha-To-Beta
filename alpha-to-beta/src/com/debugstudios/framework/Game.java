/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2013] [Antonis Kalou (kalouantonis@gmail.com)]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.debugstudios.framework;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.debugstudios.framework.screens.GameScreen;
import com.debugstudios.framework.utils.Cleanup;

import java.util.Stack;

public abstract class Game implements ApplicationListener
{
    private static final String TAG = Game.class.getSimpleName();

    GameScreen screen;

    // TODO: implement stack structure
//    private Stack<GameScreen> screenStack;

    // Screen assets can be loaded here
    AssetManager assetManager;

    private static int FPS = 60;
    // Time for each frame
//    private static float FRAME_TIME = 1.f / (float)FPS;

    public Game()
    {
//        screenStack = new Stack<GameScreen>();
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

        // Clean up heap when game is inactive
        Gdx.app.debug(TAG, "Requesting GC...");
        Cleanup.requestGC();
        Gdx.app.debug(TAG, "GC Requested.");
    }

    @Override
    public void resize(int width, int height)
    {
        screen.resize(width, height);
    }

    @Override
    public void render()
    {
        screen.pollInput();

        float deltaTime = Gdx.graphics.getDeltaTime();

        // FIXME: Check device frame rate
        if(deltaTime > 0.1f)
            deltaTime = 0.1f;

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
