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

import com.badlogic.gdx.math.MathUtils;
import com.debugstudios.framework.gameobjects.DynamicEntity;
import com.debugstudios.framework.gameobjects.Entity;

import java.util.ArrayList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Antonis Kalou
 * Date: 07/11/13
 * Time: 17:49
 */
public class SpatialHashGrid
{
    List<Entity>[] dynamicCells;
    List<Entity>[] staticCells;

    int cellsPerRow;
    int cellsPerCol;

    float cellSize;
    // Contains all cells an object call collide with
    int[] cellIds = new int[4];

    List<Entity> foundObjects;

    @SuppressWarnings("unchecked")
    public SpatialHashGrid(float worldWidth, float worldHeight, float cellSize)
    {
        this.cellSize = cellSize;

        this.cellsPerRow = MathUtils.ceil(worldWidth / cellSize);
        this.cellsPerCol = MathUtils.ceil(worldHeight / cellSize);

        int numCells = cellsPerRow * cellsPerCol;

        dynamicCells = new List[numCells];
        staticCells = new List[numCells];

        for(int i = 0; i < numCells; ++i)
        {
            dynamicCells[i] = new ArrayList<Entity>(10);
            staticCells[i] = new ArrayList<Entity>(10);
        }

        foundObjects = new ArrayList<Entity>(10);
    }

    public void insertStaticObject(Entity obj)
    {
        int[] cellIds = getCellIds(obj);

        int i = 0;
        int cellId = -1;

        while(i < cellIds.length && (cellId = cellIds[i++]) != -1)
            staticCells[cellId].add(obj);
    }

    public void insertDynamicObject(DynamicEntity obj)
    {
        int[] cellIds = getCellIds(obj);

        int i = 0;
        int cellId = -1;

        while(i < cellIds.length && (cellId = cellIds[i++]) != -1)
            dynamicCells[cellId].add(obj);
    }

    public void removeObject(Entity obj)
    {
        int[] cellIds = getCellIds(obj);
        int i = 0;
        int cellId = -1;

        while(i <= cellIds.length && (cellId = cellIds[i++]) != -1)
        {
            dynamicCells[cellId].remove(obj);
            dynamicCells[cellId].remove(obj);
        }
    }

    public void clearDynamicCells()
    {
        int len = dynamicCells.length;

        for(int i = 0; i < len; ++i)
        {
            dynamicCells[i].clear();
        }
    }

    public void clearStaticCells()
    {
        int len = staticCells.length;

        for (int i = 0; i < len; ++i)
        {
           staticCells[i].clear();
        }
    }

    public void clearAllCells()
    {
        // Both static and dynamic cells are same size
        int len = staticCells.length;

        for (int i = 0; i < len; ++i)
        {
            staticCells[i].clear();
            dynamicCells[i].clear();
        }
    }

    public List<Entity> getPotentialColliders(Entity obj)
    {
        foundObjects.clear();

        int[] cellIds = getCellIds(obj);

        int i = 0;
        int cellId = -1;

        while(i < cellIds.length && (cellId = cellIds[i++]) != -1)
        {
            int len = dynamicCells[cellId].size();

            for(int j = 0; j < len; ++j)
            {
                Entity collider = dynamicCells[cellId].get(j);
                if(!foundObjects.contains(collider))
                    foundObjects.add(collider);
            }

            len = staticCells[cellId].size();
            for(int j = 0; j < len; ++j)
            {
                Entity collider = staticCells[cellId].get(j);
                if(!foundObjects.contains(collider))
                    foundObjects.add(collider);
            }
        }

        return foundObjects;
    }

    public int[] getCellIds(Entity obj)
    {
        // Cell coordinates of object bounding rectangle
        // Relative

        // Lower left
        int x1 = MathUtils.floor(obj.position.x / cellSize);
        int y1 = MathUtils.floor((obj.position.y + obj.height) / cellSize);
        // Top right
        int x2 = MathUtils.floor((obj.position.x + obj.width) / cellSize);
        int y2 = MathUtils.floor((obj.position.y) / cellSize);

        // Item contained withing one cell
        if(x1 == x2 && y1 == y2)
        {
            if(x1 >= 0 && x1 < cellsPerRow && y1 >= 0 && y1 < cellsPerCol)
                cellIds[0] = x1 + y1 * cellsPerRow;
            else
                cellIds[0] = -1;

            cellIds[1] = -1;
            cellIds[2] = -1;
            cellIds[3] = -1;
        }
        // The object overlaps 2 cells horizontally
        else if(x1 == x2)
        {
            int i = 0;

            if(x1 >= 0 && x1 < cellsPerRow)
            {
                if(y1 >= 0 && y1 < cellsPerCol)
                    cellIds[i++] = x1 + y1 * cellsPerRow;
                if(y2 >= 0 && y2 < cellsPerCol)
                    cellIds[i++] = x1 + y2 * cellsPerRow;

                while(i < cellIds.length) cellIds[i++] = -1;
            }
        }
        // Overlaps 2 cells vertically
        else if(y1 == y2)
        {
            int i = 0;
            if(y1 >= 0 && y1 < cellsPerCol)
            {
                if(x1 >= 0 && x1 < cellsPerRow)
                    cellIds[i++] = x1 + y1 * cellsPerRow;
                if(x2 >= 0 && x2 < cellsPerRow)
                    cellIds[i++] = x2 + y1 * cellsPerRow;
            }

            while(i < cellIds.length) cellIds[i++] = -1;
        }
        // Overlaps 4 cells
        else
        {
            int i = 0;
            int y1CellsPerRow = y1 * cellsPerRow;
            int y2CellsPerRow = y2 * cellsPerRow;

            if(x1 >= 0 && x1 < cellsPerRow && y1 >= 0 && y1 < cellsPerCol)
                cellIds[i++] = x1 + y1CellsPerRow;
            if(x2 >= 0 && x2 < cellsPerRow && y1 >= 0 && y1 < cellsPerCol)
                cellIds[i++] = x2 + y1CellsPerRow;
            if(x2 >= 0 && x2 < cellsPerRow && y2 >= 0 && y2 < cellsPerCol)
                cellIds[i++] = x2 + y2CellsPerRow;
            if(x1 >= 0 && x1 < cellsPerRow && y2 >= 0 && y2 < cellsPerCol)
                cellIds[i++] = x1 + y2CellsPerRow;

            while(i < cellIds.length) cellIds[i++] = -1;
        }

        return cellIds;
    }
}
