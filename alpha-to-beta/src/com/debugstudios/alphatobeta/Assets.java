/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.maps.tiled.TiledMap;
import com.badlogic.gdx.maps.tiled.TmxMapLoader;
import com.badlogic.gdx.utils.Array;

/**
 * Created by slacker on 12/9/13.
 *
 * @author Slacker
 */
public class Assets
{
    public static TiledMap map = null;

    public static TextureAtlas humanPlayerSheet = null;

    public static Animation createLoopAnimation(float animSpeed, TextureAtlas atlas, String ... regionNames)
    {
        Array<TextureRegion> textureRegions = new Array<TextureRegion>(regionNames.length);

       for(String region : regionNames)
       {
            textureRegions.add(atlas.findRegion(region));
       }

        Animation anim = new Animation(animSpeed, textureRegions);
        anim.setPlayMode(Animation.LOOP);

        return anim;
    }

    // TODO: Thread this and check if loaded while loading
    public static void loadTextures()
    {
        humanPlayerSheet = new TextureAtlas("img/player.txt");

    }

    public static void load()
    {
        loadTextures();
        loadMap("maps/map.tmx");

        Assets.HumanPlayer.load();
    }

    public static void loadMap(String internalFile)
    {
        if(map != null)
            // Clear previous map
            map.dispose();

        map = new TmxMapLoader().load(internalFile);
    }

    public static void unload()
    {
        humanPlayerSheet.dispose();

        if(map != null)
            map.dispose();
    }

    /**
     * Created by Slacker on 17/12/13.
     */
    public static class HumanPlayer extends Player
    {
        public static void load()
        {
            ANIMATION_SPEED = 0.1f;

            // TODO: Load from HumanPlayer.xml
           runLeftAnimation = createLoopAnimation(ANIMATION_SPEED, humanPlayerSheet,
                   "left1", "left2", "left3");
           runRightAnimation = createLoopAnimation(ANIMATION_SPEED, humanPlayerSheet,
                    "right1", "right2", "right3");
           idleAnimation = createLoopAnimation(ANIMATION_SPEED + 0.15f, humanPlayerSheet,
                    "still1", "still2");

            // Grab from random texture region, they're all the same.
            // TODO: Load from HumanPlayer.xml
            textureWidth = idleAnimation.getKeyFrame(0).getRegionWidth();
            textureHeight = idleAnimation.getKeyFrame(0).getRegionHeight();
        }
    }

    /**
     * Created by Slacker on 17/12/13.
     */
    public abstract static class Player
    {
        public static float ANIMATION_SPEED = 0.2f;

        public static Animation runRightAnimation;
        // TODO: Redundant Left & Idle
        public static Animation runLeftAnimation;
        public static Animation idleAnimation;

        public static float textureWidth = 1;
        public static float textureHeight = 1;

        /**
         * Load all assets for view
         */
        public static void load()
        {

        }
    }
}
