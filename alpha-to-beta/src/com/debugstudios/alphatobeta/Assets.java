package com.debugstudios.alphatobeta;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.maps.tiled.TiledMap;
import com.badlogic.gdx.maps.tiled.TmxMapLoader;
import com.badlogic.gdx.utils.Array;

import java.util.ArrayList;

/**
 * Created by slacker on 12/9/13.
 */
public class Assets
{
    public static TiledMap map = null;

    public static TextureAtlas humanPlayer = null;
    public static Animation runRightAnimation = null;
    public static Animation runLeftAnimation = null;
    public static Animation idleAnimation = null;

    public static float PLAYER_ANIMATION_SPEED = 0.1f;

    private static Animation createLoopAnimation(float animSpeed, TextureAtlas atlas, String ... regionNames)
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
    public static void load()
    {
        humanPlayer = new TextureAtlas("img/player.txt");
        runRightAnimation = createLoopAnimation(PLAYER_ANIMATION_SPEED, humanPlayer, "right1", "right2", "right3");

        runLeftAnimation = createLoopAnimation(PLAYER_ANIMATION_SPEED, humanPlayer, "left1", "left2", "left3");

        idleAnimation = createLoopAnimation(PLAYER_ANIMATION_SPEED + 0.1f, humanPlayer, "still1", "still2");

        loadMap("maps/map.tmx");
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
        humanPlayer.dispose();

        if(map != null)
            map.dispose();
    }
}
