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

package com.debugstudios.framework.graphics;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;
import com.debugstudios.framework.gameobjects.Entity;

public class Camera extends OrthographicCamera
{
    /** Used for logging */
    private final String LOG_TAG = Camera.class.getName();

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

        // Positive Y
        //this.setToOrtho(false, viewportWidth, viewportHeight);

        Gdx.app.debug(LOG_TAG, "Viewport --> width: " + viewportWidth + ", height: " + viewportHeight);

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
