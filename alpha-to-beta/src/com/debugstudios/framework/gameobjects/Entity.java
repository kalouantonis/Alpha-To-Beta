package com.debugstudios.framework.gameobjects;

import com.badlogic.gdx.math.Vector2;


/**
 * Contains entity data and operations
 *
 * @author Antonis Kalou
 */
public class Entity
{
    public Vector2 position;
    public float width, height;
    public final Vector2 origin;

    public Entity(float x, float y, float width, float height)
    {
        this.position = new Vector2(x, y);
        this.width = width;
        this.height = height;
        this.origin = new Vector2(width / 2, height / 2);
    }
}
