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
