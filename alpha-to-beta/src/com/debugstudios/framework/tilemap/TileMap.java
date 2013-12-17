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
    private TiledMap internalTileMap;
    private OrthogonalTiledMapRenderer tileRenderer;
    private OrthographicCamera camera = null;

    // Used for reloading
    private String prevMapFile = null;

    /**
     * Load Tile Map using internal assets file
     *
     * @param internalFile assets file stored internaly
     */
    public TileMap(String internalFile)
    {
        this(new TmxMapLoader().load(internalFile));

        prevMapFile = internalFile;
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
        if(prevMapFile == null)
            throw new RuntimeException("No previous tile map to load");

        reload(prevMapFile);
    }

    public void drawLayer(TiledMapTileLayer layer)
    {
        updateCameraView();

        tileRenderer.renderTileLayer(layer);
    }

    public void drawLayers(int[] layers)
    {
        updateCameraView();

        tileRenderer.render(layers);
    }

    private void updateCameraView()
    {
        if(camera != null)
            tileRenderer.setView(camera);
    }

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

    /////////////////////////////////////////////////////////////////////////////////////
}
