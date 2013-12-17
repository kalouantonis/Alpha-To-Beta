/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2013] [Antonis Kalou (kalouantonis@gmail.com)]
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

package com.debugstudios.framework.tilemap;

import com.badlogic.gdx.maps.tiled.TiledMapTileLayer;

/**
 * Abstract class for layers
 *
 * @author Antonis Kalou
 */
public abstract class AbstractLayer
{
    /**
     * Tile layer used by collision layer
     */
    protected TiledMapTileLayer mapLayer;

    // Getters and Setters /////////////////////////////////////////////////////////////////////////////////

    /**
     * @return tile map layer used
     */
    public TiledMapTileLayer getMapLayer()
    {
        return mapLayer;
    }

    /**
     * @param mapLayer new tile map layer to use
     */
    public void setMapLayer(TiledMapTileLayer mapLayer)
    {
        this.mapLayer = mapLayer;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Delegate Methods ////////////////////////////////////////////////////////////////////////////////////

    /**
     * Delegate method of TiledMapTileLayer
     *
     * @return width of tile layer
     */
    public int getWidth()
    {
        return mapLayer.getWidth();
    }

    /**
     * Delegate method of TiledMapTileLayer
     *
     * @return height of tile layer
     */
    public int getHeight()
    {
        return mapLayer.getHeight();
    }

    /**
     * Delegate method of TiledMapTileLayer
     *
     * @return height of tiles
     */
    public float getTileWidth()
    {
        return mapLayer.getTileWidth();
    }

    /**
     * Delegate method of TiledMapTileLayer
     *
     * @return width of tiles
     */
    public float getTileHeight()
    {
        return mapLayer.getTileHeight();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Construct empty layer
     *
     * @param width      layer width
     * @param height     layer height
     * @param tileWidth  tile width
     * @param tileHeight tile height
     */
    public AbstractLayer(int width, int height, int tileWidth, int tileHeight)
    {
        mapLayer = new TiledMapTileLayer(width, height, tileWidth, tileHeight);
    }

    /**
     * Create layer using TiledMapTileLayer object
     *
     * @param layer layer object
     */
    public AbstractLayer(TiledMapTileLayer layer)
    {
        this.mapLayer = layer;
    }
}
