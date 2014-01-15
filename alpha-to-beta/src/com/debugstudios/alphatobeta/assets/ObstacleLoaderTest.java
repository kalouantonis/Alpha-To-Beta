/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 1 2014
 */

package com.debugstudios.alphatobeta.assets;

import com.debugstudios.alphatobeta.obstacles.Obstacle;
import com.debugstudios.alphatobeta.obstacles.ObstacleFactory;
import junit.framework.Assert;
import org.junit.Test;

/**
 * Created by Antonis Kalou on 1/15/14.
 */
public class ObstacleLoaderTest
{
    @Test
    public void testLoad() throws Exception
    {
        ObstacleLoader loader = new ObstacleLoader();
        ObstacleFactory factory = new ObstacleFactory();

        loader.load("/home/slacker/IdeaProjects/alpha-to-beta/alpha-to-beta-android/assets/objects/obstacles/rock.xml", factory);

        Obstacle rock = factory.create("rock", 0, 0);

        Assert.assertTrue(rock.width == 16);
        Assert.assertTrue(rock.height == 16);
        Assert.assertTrue(rock.mass == 2);
        Assert.assertTrue(rock.slowdown == 0.1f);
        Assert.assertTrue(rock.damage == 10);
    }

    @Test
    public void testLoadDirectory() throws Exception
    {
        ObstacleLoader loader = new ObstacleLoader();
        ObstacleFactory factory = new ObstacleFactory();

        loader.loadDirectory("/home/slacker/IdeaProjects/alpha-to-beta/alpha-to-beta-android/assets/objects/obstacles",
                factory, false);

        Obstacle tmpObstacle = factory.create("rock", 0, 0);

        Assert.assertTrue(tmpObstacle.width == 16);
        Assert.assertTrue(tmpObstacle.height == 16);
        Assert.assertTrue(tmpObstacle.mass == 2);
        Assert.assertTrue(tmpObstacle.slowdown == 0.1f);
        Assert.assertTrue(tmpObstacle.damage == 10);

        tmpObstacle = factory.create("tree", 0, 0);

        Assert.assertTrue(tmpObstacle.width == 8);
        Assert.assertTrue(tmpObstacle.height == 16);
        Assert.assertTrue(tmpObstacle.mass == 7);
        Assert.assertTrue(tmpObstacle.slowdown == 1);
        Assert.assertTrue(tmpObstacle.damage == 1);
    }
}
