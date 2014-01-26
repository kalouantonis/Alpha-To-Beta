/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.maps.objects.RectangleMapObject;
import com.badlogic.gdx.maps.tiled.TiledMapTileLayer;
import com.debugstudios.alphatobeta.obstacles.ObstacleFactory;
import com.debugstudios.alphatobeta.players.HumanPlayer;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.framework.datastructures.SpatialHashGrid;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.framework.tilemap.CollisionLayer;
import com.debugstudios.framework.tilemap.TileMap;

import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by Antonis Kalou on 12/9/13.
 */
public class World
{
    private static final String TAG = World.class.getSimpleName();

    public static final float WORLD_WIDTH = 480;
    public static final float WORLD_HEIGHT = 360;

    private final int NUM_PLAYERS = 5;

    public TileMap tileMap;
    private Camera camera;

    public Player player = null;
    // NOTE: If using threads, use Vector --> Is the very bestest best when thread run...
    public ArrayList<Player> players;
    public SpatialHashGrid obstacleGrid;

    public World()
    {
        this.camera = new Camera(WORLD_WIDTH, WORLD_HEIGHT);

        Gdx.app.debug(TAG, "Created camera. Viewport --> width: " + WORLD_WIDTH + "\theight: " + WORLD_HEIGHT);

        this.tileMap = new TileMap();
        this.tileMap.setCamera(camera);

        players = new ArrayList<Player>(NUM_PLAYERS);

        obstacleGrid = new SpatialHashGrid(WORLD_WIDTH, WORLD_HEIGHT, WORLD_WIDTH / 2.f);

        // TODO: Thread this, show loading screen
        reloadScene();
    }

    public void pollInput()
    {
        if(Gdx.input.isKeyPressed(Input.Keys.R))
            reloadScene();

        if(Gdx.input.isKeyPressed(Input.Keys.PLUS))
            player.MOVE_VELOCITY += 10;
        else if(Gdx.input.isKeyPressed(Input.Keys.MINUS))
            player.MOVE_VELOCITY -= 10;
        else if(Gdx.input.isKeyPressed(Input.Keys.ESCAPE))
            Gdx.app.exit();
        // Only for debugging
        else if(Gdx.input.isKeyPressed(Input.Keys.CONTROL_LEFT))
            camera.addZoom(0.1f);
        else if(Gdx.input.isKeyPressed(Input.Keys.SHIFT_LEFT))
            camera.addZoom(-0.1f);
    }

    private void reloadScene()
    {

        Gdx.app.debug(TAG, "Reloading scene...");

        //tileMap.reload();
        Assets.mapLoader.load("objects/maps/map2.xml", tileMap);
        tileMap.getCamera().zoom = 1.f;
        Gdx.app.debug(TAG, "Reloaded tile map.");

        // Reset collision layer
        Gdx.app.debug(TAG, "Reloaded collision layer.");

        RectangleMapObject spawnPos = (RectangleMapObject) tileMap.getLayer("objects").getObjects().get("SpawnPosition");
        if(player == null)
        {
            try
            {
                player = new HumanPlayer(spawnPos.getRectangle().x, spawnPos.getRectangle().y);
            }
            catch (NullPointerException e)
            {
                throw new RuntimeException("No spawn point implemented! Add a SpawnPoint object to the map" +
                                            tileMap.getFileName() != null ? ": " + tileMap.getFileName() : "");
            }
            // Add to array, keep reference for direct access
            players.add(player);

            camera.setTarget(player);
        }
        else
        {
            player.position.x = spawnPos.getRectangle().x;
            player.position.y = spawnPos.getRectangle().y;
            player.velocity.set(0, 0);
        }

        player.setCollisionLayer(new CollisionLayer(tileMap.getTileLayer(1)));

        // Load rest of attributes from loaders
        Assets.playerLoader.load("objects/players/HumanPlayer.xml", player, Assets.humanPlayerSheet);

        Gdx.app.debug(TAG, "Player loaded.");

        // Load obstacles
        ObstacleFactory factory = new ObstacleFactory();
        Assets.obstacleLoader.loadDirectory("objects/obstacles", factory, false);

        // TODO: load layer index from conf file
        // TODO: parse blocks of map, request new data every 1000 tiles or so
        TiledMapTileLayer objectLayer = tileMap.getTileLayer(2);
        int layerWidth = objectLayer.getWidth();
        int layerHeight = objectLayer.getHeight();
        float tileWidth = objectLayer.getTileWidth();
        float tileHeight = objectLayer.getTileHeight();

        Iterator<String> keyIter;
        String id;

        for(int x = 0; x < layerWidth; ++x)
        {
            for(int y = 0; y < layerHeight; ++y)
            {
                TiledMapTileLayer.Cell cell = objectLayer.getCell(x, y);

                if(cell != null)
                {
                    // Find property of cell
                    keyIter = cell.getTile().getProperties().getKeys();
                    while(keyIter.hasNext())
                    {
                        id = keyIter.next();

                        // Check if contained within factory
                        if(factory.contains(id))
                        {
                            // Insert in to obstacle grid
                            obstacleGrid.insertStaticObject(
                                    factory.create(
                                            // ID from object
                                            id,
                                            // X World coords
                                            x * tileWidth,
                                            // Y World coords. Y is inverted
                                            y * tileHeight
                                    )
                            );

                            break;
                        }
                    }
                }
            }
        }

        Gdx.app.debug(TAG, "Scene reloaded successfully!");
    }

    public void update(float deltaTime)
    {
        if(!obstacleGrid.getPotentialColliders(player).isEmpty())
        {
            Gdx.app.log(TAG, "Potential Collision with obstacle");
        }

        updateCharacters(deltaTime);

        if(player.position.y < 0)
            reloadScene();
    }

    private void updateCharacters(float deltaTime)
    {
        for(Player character : players)
        {
            character.update(deltaTime);
        }
    }

    public Camera getCamera()
    {
        return camera;
    }

    public void dispose()
    {
        tileMap.dispose();
    }
}
