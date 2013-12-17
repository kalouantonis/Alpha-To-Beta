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

package com.debugstudios.framework.screens;


public interface GameScreen
{
    /**
     * Handle polling input
     */
    public void pollInput();

    /**
     * Update the game screens
     *
     * @param delta The delta time between calls to update
     */
    public void update(float delta);

    /**
     * Draw changes
     */
    public void draw();

    /**
     * Called when game is paused, also when exited
     */
    public void pause();

    /**
     * Resume from previous pause, called when app starts
     */
    public void resume();

    /**
     * Dispose objects
     */
    public void dispose();

    /**
     * Resize screen
     *
     * @param width Width of viewport
     * @param height Height of viewport
     */
    public void resize(int width, int height);

}
