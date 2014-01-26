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

package com.debugstudios.framework.graphics;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;
import com.debugstudios.framework.gameobjects.Entity;

public class Camera extends OrthographicCamera
{
    /** Used for logging */
    private final String LOG_TAG = Camera.class.getSimpleName();

    // Default values ==============================
    /** Maximum amount of zoom in allowed */
    private final float MAX_ZOOM_IN = 0.25f;
    /** Maximum amount of zoom out allowed */
    private final float MAX_ZOOM_OUT = 10.f;
    /** Default vieport width */
    public static final float VIEWPORT_WIDTH = 480.f;
    /** Default vieport height */
    public static final float VIEWPORT_HEIGHT = 460.f;

    /** Entity to follow */
    Entity target = null;

    /**
     * Create new camera with specified viewport parameters
     *
     * @param viewportWidth     Width of viewport
     * @param viewportHeight    Height of viewport
     */
    public Camera(float viewportWidth, float viewportHeight)
    {
        super(viewportWidth, viewportHeight);

        this.position.set(0, 0, 0);
        this.zoom = 1.f;

        this.update();
    }

    /**
     * Create new camera with default viewport diameters
     */
    public Camera()
    {
        this(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    }

    /**
     * Add zoom on to current zoom
     *
     * @param amount The amount of zoom to add
     */
    public void addZoom(float amount)
    {
        this.setZoom(this.zoom + amount);
    }

    /**
     * Set the amount of zoom
     *
     * @param zoom Zoom amount
     */
    public void setZoom(float zoom)
    {
        this.zoom = MathUtils.clamp(zoom, MAX_ZOOM_IN, MAX_ZOOM_OUT);
    }

    /**
     * Set target for camera to follow
     *
     * @param target Entity target to follow
     */
    public void setTarget(Entity target)
    {
       this.target = target;
    }

    /**
     * Get the current target that camera is following
     *
     * @return Current Camera target
     */
    public Entity getTarget()
    {
        return target;
    }

    /**
     * Checks if target exists
     *
     * @return True if exists
     */
    public boolean hasTarget() { return target != null; }

    /**
     * Checks if target exists
     *
     * @param target Specified target to check
     * @return  True if exists
     */
    public boolean hasTarget(Entity target)
    {
        return hasTarget() && this.target.equals(target);
    }

    /**
     * Update camera
     */
    @Override
    public void update()
    {
        if(hasTarget())
        {
            this.position.x = target.position.x + target.origin.x;
            this.position.y = target.position.y + target.origin.y;
        }

        // Update camera
        super.update();
    }

    /**
     * Transform touch co-ordinates on screen to camera world co-ordinates
     *
     * @param touch Touch position, screen position
     */
    public void touchToWorld(Vector2 touch)
    {
        touch.x = (touch.x / (float) Gdx.graphics.getWidth()) * viewportWidth * zoom;
        touch.y = (1 - touch.y / (float)Gdx.graphics.getHeight()) * viewportHeight * zoom;
        touch.add(position.x, position.y).sub(viewportWidth * zoom / 2, viewportHeight * zoom / 2);
    }
}
