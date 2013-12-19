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
import com.debugstudios.alphatobeta.players.HumanPlayer;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.framework.tilemap.CollisionLayer;
import com.debugstudios.framework.tilemap.TileMap;

import java.util.ArrayList;

/**
 * Created by Antonis Kalou on 12/9/13.
 */
public class World
{
    private final int NUM_PLAYERS = 5;

    public static final float WORLD_WIDTH = 480;
    public static final float WORLD_HEIGHT = 360;

    public TileMap tileMap;
    public CollisionLayer collisionLayer;

    public Player player = null;
    // NOTE: If using threads, use Vector --> Is the very bestest best when thread run...
    public ArrayList<Player> players;

    public World(TileMap tileMap)
    {
        this.tileMap = tileMap;

        collisionLayer = new CollisionLayer(tileMap.getTileLayer(1));

        players = new ArrayList<Player>(NUM_PLAYERS);

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
    }

    private void reloadScene()
    {
        tileMap.reload();

        RectangleMapObject spawnPos = (RectangleMapObject) tileMap.getLayer("objects").getObjects().get("SpawnPosition");
        if(player == null)
        {
            try
            {
                player = new HumanPlayer(spawnPos.getRectangle().x, spawnPos.getRectangle().y);
                player.setCollisionLayer(collisionLayer);
            }
            catch (NullPointerException e)
            {
                throw new RuntimeException("No spawn point implemented! Add a SpawnPoint object to the map" +
                                            tileMap.getFileName() != null ? ": " + tileMap.getFileName() : "");
            }
            // Add to array, keep reference for direct access
            players.add(player);
        }
        else
        {
            player.position.x = spawnPos.getRectangle().x;
            player.position.y = spawnPos.getRectangle().y;
        }
    }

    public void update(float deltaTime)
    {
        updateCharacters(deltaTime);
    }

    private void checkCharacterCollisions()
    {
    }

    private void updateCharacters(float deltaTime)
    {
        for(Player character : players)
        {
            character.update(deltaTime);
        }
    }
}
