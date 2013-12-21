/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2013] [Antonis Kalou (kalouantonis@gmail.com)]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.debugstudios.framework.graphics;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.utils.Array;

/**
 * Created by Antonis Kalou on 20/12/13.
 */
public class AnimUtils
{
    private static Animation createAnimation(float animSpeed, int animType, TextureAtlas atlas, String ... regionNames)
    {
        Array<TextureRegion> textureRegions = new Array<TextureRegion>(regionNames.length);

       for(String region : regionNames)
       {
            textureRegions.add(atlas.findRegion(region));
       }

        Animation anim = new Animation(animSpeed, textureRegions);
        anim.setPlayMode(animType);

        return anim;
    }

    private static Animation createAnimation(float animSpeed, int animType, TextureAtlas atlas, Array<String> regionNames)
    {
        Array<TextureRegion> textureRegions = new Array<TextureRegion>(regionNames.size);

        for(String region : regionNames)
        {
            textureRegions.add(atlas.findRegion(region));
        }

        Animation anim = new Animation(animSpeed, textureRegions);
        anim.setPlayMode(animType);

        return anim;
    }

    public static Animation createLoopAnimation(float animSpeed, TextureAtlas atlas, String ... regionNames)
    {
        return createAnimation(animSpeed, Animation.LOOP, atlas, regionNames);
    }

    public static Animation createLoopAnimation(float animSpeed, TextureAtlas atlas, Array<String> regionNames)
    {
        return createAnimation(animSpeed, Animation.LOOP, atlas, regionNames);
    }

    public static Animation createNormalAnimation(float animSpeed, TextureAtlas atlas, String ... regionNames)
    {
        return createAnimation(animSpeed, Animation.NORMAL, atlas, regionNames);
    }

    public static Animation createNormalAnimation(float animSpeed, TextureAtlas atlas, Array<String> regionNames)
    {
        return createAnimation(animSpeed, Animation.NORMAL, atlas, regionNames);
    }
}
