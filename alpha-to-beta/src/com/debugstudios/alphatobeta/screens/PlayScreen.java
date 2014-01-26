/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.controllers.Controllers;
import com.badlogic.gdx.controllers.mappings.Ouya;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.debugstudios.alphatobeta.Assets;
import com.debugstudios.alphatobeta.World;
import com.debugstudios.alphatobeta.input.PlayerInputHandler;
import com.debugstudios.alphatobeta.input.PlayerOuyaHandler;
import com.debugstudios.alphatobeta.input.PlayerTouchHandler;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.alphatobeta.renderers.WorldDebugRenderer;
import com.debugstudios.alphatobeta.renderers.WorldRenderer;
import com.debugstudios.framework.Game;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.framework.screens.GameScreen;
import com.debugstudios.framework.tilemap.TileMap;
import com.debugstudios.framework.utils.Debug;


/**
 * Created by slacker on 12/7/13.
 */
public class PlayScreen implements GameScreen
{
    private static final String TAG = PlayScreen.class.getSimpleName();

    private WorldRenderer worldRenderer;
    private WorldDebugRenderer debugRenderer;

    private World world;

    public PlayScreen(Game game)
    {
        Assets.loadAll();


        world = new World();

        SpriteBatch spriteBatch = world.tileMap.getSpriteBatch();
        worldRenderer = new WorldRenderer(spriteBatch, world);
        debugRenderer = new WorldDebugRenderer(spriteBatch, world);


        switch (Gdx.app.getType())
        {
            case Android:
                // TODO: Check if Ouya registers as android app
                Gdx.input.setInputProcessor(new PlayerTouchHandler(world));
                Gdx.app.debug(TAG, "Using Android input handler");
                break;
            case Desktop:
                Gdx.input.setInputProcessor(new PlayerInputHandler(world));
                Gdx.app.debug(TAG, "Using Desktop input handler");
                break;
            default:
                throw new RuntimeException("Unsupported platform!");
        }

        if(Ouya.runningOnOuya)
            Controllers.addListener(new PlayerOuyaHandler(world));

        Gdx.gl.glClearColor(135.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1);
    }

    @Override
    public void pollInput()
    {
        world.pollInput();

        if(Gdx.input.isKeyPressed(Input.Keys.G))
        {
            Debug.dumpHeap(TAG);
        }
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

        // Dispose sequence is important.
        // Remove items that reference world data first
        worldRenderer.dispose();
        world.dispose();
    }

    @Override
    public void resize(int width, int height)
    {
    }
}
