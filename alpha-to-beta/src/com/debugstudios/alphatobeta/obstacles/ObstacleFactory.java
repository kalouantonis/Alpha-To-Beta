/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 1 2014
 */

package com.debugstudios.alphatobeta.obstacles;

import com.debugstudios.framework.entities.EntityFactory;

/**
 * Created by Antonis Kalou on 1/10/14.
 */
/*public class ObstacleFactory
{
    private TreeMap<String, Obstacle> obstacleTemplateMap;

    public ObstacleFactory()
    {
        obstacleTemplateMap = new TreeMap<String, Obstacle>();
    }

    public Obstacle create(String tag, float x, float y)
    {
        // Create new obstacle using copy constructor
        // TODO: Use pool
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

    public boolean contains(String id)
    {
        return obstacleTemplateMap.containsKey(id);
    }
}*/

// TODO: Make singleton. In this way we can create new object anywhere
// TODO: If attribute "id" exists, add it to the factory and then
// TODO: re-use it any time it is detected within a context
// TODO: Maybe use this for every object. Give an "id" and load it
// TODO: according to if it exists in the factory, avoid double loading
public class ObstacleFactory extends EntityFactory<Obstacle>
{
    @Override
    public Obstacle create(String tag, float x, float y)
    {
        return new Obstacle(entityTemplateMap.get(tag), x, y);
    }
}
