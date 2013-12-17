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

package com.debugstudios.framework.gameobjects;

import com.badlogic.gdx.math.Vector2;

/**
 * Entity for drawable objects
 *
 * @author Antonis Kalou
 */
public abstract class DynamicEntity extends Entity
{
    /** Entity X and Y velocity */
    public final Vector2 velocity;
    /** Entity X and Y acceleration */
    public final Vector2 accel;

    public DynamicEntity(float x, float y, float width, float height)
    {
        super(x, y, width, height);

        velocity = new Vector2(0, 0);
        accel = new Vector2(0, 0);
    }

    /**
     * Update entity according to delta time.
     * All dynamic entities will need to perform this/
     *
     * @param deltaTime Tile elapsed since last update call
     */
    public abstract void update(float deltaTime);
}
