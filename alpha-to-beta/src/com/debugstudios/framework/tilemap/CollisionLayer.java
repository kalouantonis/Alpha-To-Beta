package com.debugstudios.framework.tilemap;

import com.badlogic.gdx.maps.tiled.TiledMapTileLayer;
import com.debugstudios.framework.gameobjects.Entity;

/**
 * TileMapLayer with support for collision detection
 *
 * @author Antonis Kalou
 */
public class CollisionLayer extends AbstractLayer
{
    public CollisionLayer(int width, int height, int tileWidth, int tileHeight)
    {
        super(width, height, tileWidth, tileHeight);
    }

    public CollisionLayer(TiledMapTileLayer layer)
    {
        super(layer);
    }

    /**
     * Check for collision using XY on the collision layer
     *
     * @param x tile X position
     * @param y tily Y position
     * @return true if collides, false if not
     */
    public boolean collides(float x, float y)
    {
        return cellContainsTile(x, y);
    }

    /**
     * Check GameObject from collision with any tile
     *
     * @param gameobject GameObject to check collision with
     * @return true if collision occurs
     */
    public boolean collides(Entity gameobject)
    {
        return collidesRight(gameobject) || collidesLeft(gameobject) ||
                collidesTop(gameobject) || collidesBottom(gameobject);
    }

    /**
     * Check for collision with right side of game object
     *
     * @param gameobject Game object to check
     * @return true if collides
     */
    public boolean collidesRight(Entity gameobject)
    {
        for(float step = 0; step <= gameobject.height; step += getTileHeight() / 2.f)
        {
            if(cellContainsTile(gameobject.position.x + gameobject.width, gameobject.position.y + step))
                return true;
        }

        return false;
    }

    /**
     * Check left side of gameobject for collisions with tile
     *
     * @param gameobject object to check
     * @return true if collides
     */
    public boolean collidesLeft(Entity gameobject)
    {
        for(float step = 0; step <= gameobject.height; step += getTileHeight() / 2.f)
        {
            if(cellContainsTile(gameobject.position.x, gameobject.position.y + step))
                return true;
        }

        return false;
    }

    /**
     * Check top side of gameobject for collisions with tile
     *
     * @param gameobject object to check
     * @return true if collides
     */
    public boolean collidesTop(Entity gameobject)
    {
        for(float step = 0; step <= gameobject.width; step += getTileWidth() / 2.f)
        {
            if(cellContainsTile(gameobject.position.x + step, gameobject.position.y + gameobject.height))
                return true;
        }

        return false;
    }

    /**
     * Check bottom side of gameobject for collisions with tile
     *
     * @param gameobject object to check
     * @return true if collides
     */
    public boolean collidesBottom(Entity gameobject)
    {
        for(float step = 0; step <= gameobject.width; step += getTileWidth() / 2.f)
        {
            if(cellContainsTile(gameobject.position.x + step, gameobject.position.y))
                return true;
        }

        return false;
    }


    /**
     * Check if cell contains tile
     *
     * @param x X position of object
     * @param y Y position of object
     * @return true if key is contained in cell, false if not
     */
    public boolean cellContainsTile(float x, float y)
    {
        // Get cell at tile position
        TiledMapTileLayer.Cell cell = mapLayer.getCell((int) (x / getTileWidth()), (int) (y / getTileHeight()));

        return cell != null && cell.getTile() != null;
    }
}
