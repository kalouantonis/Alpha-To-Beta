/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2014] [Antonis Kalou (kalouantonis@gmail.com)]
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

package com.debugstudios.framework.datastructures;

import com.badlogic.gdx.math.Rectangle;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Created by Antonis Kalou on 1/26/14.
 */
public class QuadTreeTest
{
    @Test
    public void testRetrieve() throws Exception
    {
        Random random = new Random();

        int worldWidth = 2000;
        int worldHeight = 1000;

        Rectangle dynamicItem = new Rectangle(random.nextInt(worldWidth), random.nextInt(worldHeight), 16, 16);
        System.out.println("Object position: " + dynamicItem);

        Rectangle[] staticItems = new Rectangle[10000];


        int len = staticItems.length;
        for(int i = 0; i < len; ++i)
        {
            int x = random.nextInt(worldWidth);
            int y = random.nextInt(worldHeight);

            staticItems[i] = new Rectangle(x, y, 16.f, 16.f);
        }

        QuadTree quadTree = new QuadTree(0, new Rectangle(0, 0, worldWidth, worldHeight));

        for(Rectangle object : staticItems)
        {
            quadTree.insert(object);
        }

        List<Rectangle> colliders = new ArrayList<Rectangle>();

        quadTree.retrieve(colliders, dynamicItem);

        System.out.println("Possible colliders: " + colliders +
                            "\nLength: " + colliders.size());

        System.out.println("Real colliders:");
        for(Rectangle possible : colliders)
        {
            if(dynamicItem.overlaps(possible))
                System.out.println("\t" + possible);
        }
    }
}
