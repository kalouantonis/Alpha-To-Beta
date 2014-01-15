/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.obstacles;

import com.debugstudios.framework.gameobjects.Entity;

/**
 * Created by Antonis Kalou on 12/30/13.
 */
public class Obstacle extends Entity
{
    public float slowdown;
    public float damage;
    public float mass;

    public Obstacle(float x, float y, float width, float height)
    {
        super(x, y, width, height);
    }

    /**
     * Copy constructor
     *
     * @param another Object to copy
     * @param x X position
     * @param y Y position
     */
    public Obstacle(Obstacle another, float x, float y)
    {
        super(x, y, another.width, another.height);

        slowdown = another.slowdown;
        damage = another.damage;
        mass = another.mass;
    }
}
