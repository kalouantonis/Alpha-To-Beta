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

package com.debugstudios.framework.entities;

import com.badlogic.gdx.math.Vector2;

/**
 * Entity for drawable objects
 *
 * @author Antonis Kalou
 */
public abstract class DynamicEntity extends Entity
{
    /** Entity X and Y velocity */
    public Vector2 velocity;
    /** Entity X and Y acceleration */
    public Vector2 accel;

    public DynamicEntity(float x, float y, float width, float height)
    {
        super(x, y, width, height);

        velocity = new Vector2(0, 0);
        accel = new Vector2(0, 0);
    }

    public DynamicEntity(DynamicEntity another, float x, float y)
    {
        this(x, y, another.width, another.height);

        this.velocity = another.velocity;
        this.accel = another.accel;
    }

    /**
     * Update entity according to delta time.
     * All dynamic entities will need to perform this/
     *
     * @param deltaTime Tile elapsed since last update call
     */
    public abstract void update(float deltaTime);
}
