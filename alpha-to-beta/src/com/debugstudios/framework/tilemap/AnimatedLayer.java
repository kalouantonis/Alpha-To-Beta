package com.debugstudios.framework.tilemap;

import com.badlogic.gdx.maps.tiled.TiledMapTileLayer;

/**
 * Layer to interact with animated tiles
 *
 * @author Antonis Kalou
 */
public class AnimatedLayer extends AbstractLayer
{
    public AnimatedLayer(int width, int height, int tileWidth, int tileHeight)
    {
        super(width, height, tileWidth, tileHeight);
    }

    public AnimatedLayer(TiledMapTileLayer layer)
    {
        super(layer);
    }
}
