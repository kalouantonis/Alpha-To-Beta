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

import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.maps.MapLayer;
import com.badlogic.gdx.maps.tiled.TiledMap;
import com.badlogic.gdx.maps.tiled.TiledMapTileLayer;
import com.badlogic.gdx.maps.tiled.TmxMapLoader;
import com.badlogic.gdx.maps.tiled.renderers.OrthogonalTiledMapRenderer;

/**
 * Class to simplify tile map operations
 *
 * @author Antonis Kalou
 */
public class TileMap
{
    /** Layer data and stuff */
    private TiledMap internalTileMap;
    /** Renderer of our tile layer */
    private OrthogonalTiledMapRenderer tileRenderer;
    /** Camera for rendering */
    // TODO: Use my camera, allow getting and setting of camera
    private OrthographicCamera camera = null;

    private String prevFile = null;

    /**
     * Load Tile Map using internal assets file
     *
     * @param internalFile assets file stored internally
     */
    public TileMap(String internalFile)
    {
        this(new TmxMapLoader().load(internalFile));

        prevFile = internalFile;
    }
    // TODO: support asset manager

    /**
     * Create TileMap using file handle
     *
     * @param fileHandle File handle to load from
     */
    public TileMap(FileHandle fileHandle)
    {
        this(fileHandle.path());
    }

    /**
     * Set pre-loaded TiledMap
     *
     * @param tiledMap Pre-loaded TiledMap
     */
    public TileMap(TiledMap tiledMap)
    {
        internalTileMap = tiledMap;

        tileRenderer = new OrthogonalTiledMapRenderer(internalTileMap);
    }

    /**
     * Render the tile map
     */
    public void draw()
    {
        updateCameraView();

        tileRenderer.render();
    }

    /**
     * Reload tile map
     *
     * @param filename Filename of TMX tilemap
     */
    public void reload(String filename)
    {
        // Delete old tile map
        internalTileMap.dispose();

        // Create new one
        internalTileMap = new TmxMapLoader().load(filename);

        // Set new map to renderer
        tileRenderer.setMap(internalTileMap);
    }

    public void reload()
    {
        reload(prevFile);
    }

    /**
     * Delegate method. Draw tile layer
     *
     * @param layer Layer to draw
     */
    public void drawLayer(TiledMapTileLayer layer)
    {
        updateCameraView();

        tileRenderer.renderTileLayer(layer);
    }

    /**
     * Draw multiple layers, using indexes
     *
     * @param layers Layers to draw
     */
    public void drawLayers(int[] layers)
    {
        updateCameraView();

        tileRenderer.render(layers);
    }

    /**
     * Update camera
     *
     * @deprecated TODO: Make this automagic, so use my own camera class
     */
    private void updateCameraView()
    {
        if(camera != null)
            tileRenderer.setView(camera);
    }

    /**
     * Dispose of internal objects
     */
    public void dispose()
    {
        internalTileMap.dispose();
        tileRenderer.dispose();
    }


    // Setters and getters //////////////////////////////////////////////////////////////

    /**
     * Get the internal renderer's sprite batch
     *
     * @return Tile renderer's sprite batch
     */
    public SpriteBatch getSpriteBatch()
    {
        return tileRenderer.getSpriteBatch();
    }

    public OrthographicCamera getCamera()
    {
        return camera;
    }

    public void setCamera(OrthographicCamera camera)
    {
        this.camera = camera;
    }

    /**
     * @return Tile map used internally
     */
    public TiledMap getInternalTileMap()
    {
        return internalTileMap;
    }

    /**
     * @param internalTileMap TiledMap to use
     */
    public void setInternalTileMap(TiledMap internalTileMap)
    {
        this.internalTileMap = internalTileMap;
    }

    /**
     * Programatically set opacity, good for optimization.
     *
     * @param layerIndex Index of layer in internal map
     * @param opacity    The normalized value of opacity used for layer
     */
    public void setLayerOpacity(int layerIndex, float opacity)
    {
        internalTileMap.getLayers().get(layerIndex).setOpacity(opacity);
    }

    /**
     * Programatically set opacity, good for optimization.
     *
     * @param layerName Name of layer
     * @param opacity   The normalized value of opacity used for layer
     */
    public void setLayerOpacity(String layerName, float opacity)
    {
        internalTileMap.getLayers().get(layerName).setOpacity(opacity);
    }

    /**
     * Get the layer opacity value
     *
     * @param layerIndex The index of the layer
     * @return the normalized opacity value
     */
    public float getLayerOpacity(int layerIndex)
    {
        return internalTileMap.getLayers().get(layerIndex).getOpacity();
    }

    /**
     * Get the layer's opacity value
     *
     * @param layerName The name of the layer
     * @return the normalized opacity value
     */
    public float getLayerOpacity(String layerName)
    {
        return internalTileMap.getLayers().get(layerName).getOpacity();
    }

    /**
     * Get layer by name. Delegate of TiledMap
     *
     * @param layerName Layer name as String
     * @return Full tile layer
     */
    public MapLayer getLayer(String layerName)
    {
        return internalTileMap.getLayers().get(layerName);
    }

    /**
     * Get layer by index. Delegate of TiledMap
     *
     * @param layerIndex index of layer
     * @return  Full tile layer
     */
    public MapLayer getLayer(int layerIndex)
    {
        return internalTileMap.getLayers().get(layerIndex);
    }

    /**
     * Get layer by index. Delegate of TiledMap
     *
     * @param layerIndex Integer index of layer
     * @return Full tile layer
     */
    public TiledMapTileLayer getTileLayer(int layerIndex)
    {
        return (TiledMapTileLayer) internalTileMap.getLayers().get(layerIndex);
    }

    public String getFileName()
    {
        return prevFile;
    }

    /////////////////////////////////////////////////////////////////////////////////////
}
