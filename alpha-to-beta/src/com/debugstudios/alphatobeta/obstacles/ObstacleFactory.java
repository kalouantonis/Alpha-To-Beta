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
    private TreeMap<String, Obstacle> obstacleTemplateMap;

    public ObstacleFactory()
    {
        obstacleTemplateMap = new TreeMap<String, Obstacle>();
    }

    public Obstacle create(String tag, float x, float y)
    {
        // Create new obstacle using copy constructor
        return new Obstacle(obstacleTemplateMap.get(tag), x, y);
    }

    public void addObstacleTemplate(String tag, Obstacle template)
    {
        obstacleTemplateMap.put(tag, template);
    }

    public void clearObstacleTemplates()
    {
        obstacleTemplateMap.clear();
    }
}
