/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 1 2014
 */

package com.debugstudios.alphatobeta.obstacles;

import java.util.TreeMap;

/**
 * Created by Antonis Kalou on 1/10/14.
 */
public class ObstacleFactory
{
    private TreeMap<String, ObstacleBuilder> obstacleBuilderMap;

    public ObstacleFactory()
    {
        obstacleBuilderMap = new TreeMap<String, ObstacleBuilder>();
    }

    public Obstacle create(String tag, float x, float y)
    {
        return obstacleBuilderMap.get(tag).create(x, y);
    }

    public void addObstacleBuilder(String tag, ObstacleBuilder factory)
    {
        obstacleBuilderMap.put(tag, factory);
    }

    public void clearObstacleBuilders()
    {
        obstacleBuilderMap.clear();
    }
}
