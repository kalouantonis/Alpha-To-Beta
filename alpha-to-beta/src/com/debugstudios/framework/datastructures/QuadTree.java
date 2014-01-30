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
import com.debugstudios.framework.entities.Entity;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Antonis Kalou on 1/26/14.
 */
public class QuadTree
{
    private final int MAX_OBJECTS = 10;
    private final int MAX_LEVELS = 5;

    /** Current node level. 0 is topmost */
    private final int level;
    private List<Entity> objects;
    /** Space that node represents */
    private Rectangle bounds;
    private QuadTree[] nodes;

    public QuadTree(int pLevel, Rectangle pBounds)
    {
        level = pLevel;
        objects = new ArrayList<Entity>();
        bounds = pBounds;
        nodes = new QuadTree[4];
    }

    /**
     * Clears quadtree including child nodes
     */
    public void clear()
    {
        objects.clear();

        int len = nodes.length;
        for(int i = 0; i < len; ++i)
        {
            if(nodes[i] != null)
            {
                nodes[i].clear();
                // Remove all references
                nodes[i] = null;
            }
        }
    }

    /**
     * Splits the node into 4 subnodes
     */
    private void split()
    {
        int subWidth = (int)(bounds.getWidth() / 2);
        int subHeight = (int)(bounds.getHeight() / 2);
        int x = (int)bounds.getX();
        int y = (int)bounds.getY();

        // Top right
        nodes[0] = new QuadTree(level + 1, new Rectangle(x + subWidth, y, subWidth, subHeight));
        // Top Left
        nodes[1] = new QuadTree(level + 1, new Rectangle(x, y, subWidth, subHeight));
        // Bottom left
        nodes[2] = new QuadTree(level + 1, new Rectangle(x, y + subHeight, subWidth, subHeight));
        // Bottom right
        nodes[3] = new QuadTree(level + 1, new Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
    }

    /**
     * Determine which node the object belongs to.
     *
     * @param pRect Rectangle area to check
     * @return Returns -1 if object can not fit withing the child nod and is part of the parent node
     */
    private int getIndex(Entity pRect)
    {
        int index = -1;

        float x = pRect.position.x;
        float y = pRect.position.y;
        float width = pRect.width;
        float height = pRect.height;

        double verticalMidpoint = bounds.getX() + (bounds.getWidth() / 2);
        double horizontalMidpoint = bounds.getY() + (bounds.getHeight() / 2);


        // Object can completelly fit within the top quadrants
        boolean topQuadrant = (y < horizontalMidpoint && y + height < horizontalMidpoint);
        // Object can completely fit within the bottom quadrants
        boolean bottomQuadrant = (y > horizontalMidpoint);

        // Object can completely fit within the left quadrants
        if(x < verticalMidpoint && x + width < verticalMidpoint)
        {
            if(topQuadrant)
            {
                index = 1;
            }
            else if(bottomQuadrant)
            {
                index = 2;
            }
        }
        // Object can completely fit within the right quadrants
        else if(x > verticalMidpoint)
        {
            if(topQuadrant)
                index = 0;
            else if(bottomQuadrant)
                index = 3;
        }

        return index;
    }

    /**
     * Insert the object into the quadtree. If the node
     * exceeds the capacity, it will be split and add all
     * objects to their corresponding nodes.
     *
     * @param pRect Object to insert
     */
    public void insert(Entity pRect)
    {
        // Determine if there are any children to add to
        if(nodes[0] != null)
        {
            int index = getIndex(pRect);

            if(index != -1)
            {
                nodes[index].insert(pRect);

                return;
            }
        }

        objects.add(pRect);

        // Split current node and add all objects that fit in to the
        // child nodes
        if(objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
        {
            if(nodes[0] == null)
            {
                split();
            }

            int i = 0;
            while(i < objects.size())
            {
                int index = getIndex(objects.get(i));
                if(index != -1)
                    nodes[index].insert(objects.remove(i));
                else
                    ++i;
            }
        }
    }

    /**
     * Return all objects that could collide with the give object
     *
     * @param returnObjects Object list to fill
     * @param pRect Object to check
     */
    public void retrieve(List<Entity> returnObjects, Entity pRect)
    {
        int index = getIndex(pRect);
        if(index != -1 && nodes[0] != null)
        {
            // check children for collisions
            nodes[index].retrieve(returnObjects, pRect);
        }

        returnObjects.addAll(objects);
    }
}
