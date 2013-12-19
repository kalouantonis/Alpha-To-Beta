/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import com.debugstudios.alphatobeta.Assets;
import com.debugstudios.alphatobeta.World;
import com.debugstudios.alphatobeta.input.PlayerInputHandler;
import com.debugstudios.alphatobeta.input.PlayerTouchHandler;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.alphatobeta.views.WorldDebugRenderer;
import com.debugstudios.alphatobeta.views.WorldRenderer;
import com.debugstudios.framework.Game;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.framework.screens.GameScreen;
import com.debugstudios.framework.tilemap.TileMap;


/**
 * Created by slacker on 12/7/13.
 */
public class PlayScreen implements GameScreen
{
    private TileMap tileMap;
    private Camera camera;

    private WorldRenderer worldRenderer;
    private WorldDebugRenderer debugRenderer;

//    private int[] backgroundLayers;
//    private int[] foregroundLayers;

    private final float WORLD_WIDTH = 480;
    private final float WORLD_HEIGHT = 360;

    World world;

    public PlayScreen(Game game)
    {
        Assets.loadAll("maps/map.tmx");

        camera = new Camera(WORLD_WIDTH, WORLD_HEIGHT);


        tileMap = Assets.map;
        tileMap.setCamera(camera);


        world = new World(tileMap);

        Player player = world.player;

        SpriteBatch spriteBatch = tileMap.getSpriteBatch();
        worldRenderer = new WorldRenderer(camera, spriteBatch, world);
        debugRenderer = new WorldDebugRenderer(camera, spriteBatch, world);

        switch (Gdx.app.getType())
        {
            case Android:
                Gdx.input.setInputProcessor(new PlayerTouchHandler(camera, player));
                break;
            case Desktop:
                Gdx.input.setInputProcessor(new PlayerInputHandler(camera, player));
                break;
            default:
                throw new RuntimeException("Unsupported platform!");
        }

        camera.setTarget(player);

        Gdx.gl.glClearColor(135.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1);
    }

    @Override
    public void pollInput()
    {
        world.pollInput();

        if(Gdx.input.isKeyPressed(Input.Keys.CONTROL_LEFT))
            camera.addZoom(0.1f);
        else if(Gdx.input.isKeyPressed(Input.Keys.SHIFT_LEFT))
            camera.addZoom(-0.1f);
    }

    @Override
    public void update(float delta)
    {
        world.update(delta);
    }

    @Override
    public void draw()
    {
        //Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);

        // Update orthos and whatnot
        //camera.update();

        //tileMap.draw();

        worldRenderer.render();
        debugRenderer.render();
    }

    @Override
    public void pause()
    {
    }

    @Override
    public void resume()
    {
        Gdx.gl.glClearColor(135.f/255.f, 206.f/255.f, 235.f/255.f, 1);
    }

    @Override
    public void dispose()
    {
        Assets.unload();
        debugRenderer.dispose();
    }

    @Override
    public void resize(int width, int height)
    {
    }
}
