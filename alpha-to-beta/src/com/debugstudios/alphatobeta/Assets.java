/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.debugstudios.alphatobeta.assets.MapLoader;
import com.debugstudios.alphatobeta.assets.ObstacleLoader;
import com.debugstudios.alphatobeta.assets.PlayerLoader;
import com.debugstudios.framework.tilemap.TileMap;

/**
 * Created by slacker on 12/9/13.
 *
 * @author Slacker
 */
public class Assets
{
    private static final String TAG = Assets.class.getSimpleName();

    public static TextureAtlas humanPlayerSheet = null;
    public static PlayerLoader playerLoader = null;
    public static MapLoader mapLoader = null;
    public static ObstacleLoader obstacleLoader = null;

    /** Do not allow instantiation */
    private Assets()
    {
        throw new AssertionError("Assets class can not be instantiated");
    }

    public static void loadAll()
    {
        loadTextures();
        Gdx.app.debug(TAG, "Textures loaded");

        mapLoader = new MapLoader();
        Gdx.app.debug(TAG, "Map Loader created");

        playerLoader = new PlayerLoader();
        Gdx.app.debug(TAG, "Player loader created");

        obstacleLoader = new ObstacleLoader();
        Gdx.app.debug(TAG, "Obstacle loader created");
    }

    public static void loadTextures()
    {
        humanPlayerSheet = new TextureAtlas("img/player.txt");
    }

    public static void unload()
    {
        humanPlayerSheet.dispose();
    }
}
