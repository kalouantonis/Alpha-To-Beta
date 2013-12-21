/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta;

import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.debugstudios.alphatobeta.assets.PlayerLoader;
import com.debugstudios.framework.tilemap.TileMap;

/**
 * Created by slacker on 12/9/13.
 *
 * @author Slacker
 */
public class Assets
{
    public static TileMap map = null;
    public static TextureAtlas humanPlayerSheet = null;
    public static PlayerLoader playerLoader = null;


    // TODO: Thread this and check if loaded while loading
    public static void loadTextures()
    {
        humanPlayerSheet = new TextureAtlas("img/player.txt");

    }

    public static void loadAll(String tileMapFile)
    {
        loadTextures();
        loadMap(tileMapFile);

        playerLoader = new PlayerLoader();
    }

    public static void loadMap(String internalFile)
    {
        if(map != null)
            // Clear previous map
            map.dispose();

        map = new TileMap(internalFile);
    }

    public static void unload()
    {
        humanPlayerSheet.dispose();

        if(map != null)
            map.dispose();
    }
}
