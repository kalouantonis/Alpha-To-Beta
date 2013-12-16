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

package com.debugstudios.alphatobeta.framework.screens;


public interface GameScreen
{
    /**
     * Handle polling input
     */
    public void handleInput();

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
