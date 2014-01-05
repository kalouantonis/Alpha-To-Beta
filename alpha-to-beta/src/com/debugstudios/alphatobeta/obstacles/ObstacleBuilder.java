/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.obstacles;

/**
 * Created by Antonis Kalou on 12/31/13.
 */
public interface ObstacleBuilder
{
    /**
     * Build a new obstacle
     *
     * @param x X position
     * @param y Y position
     * @return The newly created obstacle
     */
    public Obstacle create(float x, float y);
}
