/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2014] [Antonis Kalou (kalouantonis@gmail.com)]
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

package com.debugstudios.framework.components;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.XmlReader;
import com.debugstudios.framework.graphics.AnimUtils;
import com.debugstudios.framework.parsers.XmlHelpers;
import com.debugstudios.framework.parsers.XmlReaderException;

/**
 * Created by Antonis Kalou on 1/29/14.
 */
public class AnimatedRenderable extends AbstractAnimation
{
    public Animation animation;

    public AnimatedRenderable()
    {
        animation = null;
    }

    public AnimatedRenderable(TextureAtlas animAtlas, float animSpeed, String ... regionNames)
    {
        AnimUtils.createLoopAnimation(animSpeed, animAtlas, regionNames);
    }

    public AnimatedRenderable(Animation animation)
    {
        this.animation = animation;
    }

    @Override
    public void load(XmlReader.Element compRoot) throws XmlReaderException
    {
        /**
         * XML defined as such:
         *
         * <Component type="com.debugstudios.framework.components.AnimatedRenderable">
         *      <AtlasFile>path/to/atlas.txt</AtlasFile>
         *      <!-- In seconds -->
         *      <AnimationSpeed>0.1</AnimationSpeed>
         *      <!-- Set to normal by default -->
         *      <AnimationType>Looping</AnimationType>
         *      <RegionNames>
         *          <Region name="left1" />
         *          <Region name="left2" />
         *      </RegionNames>
         * </Component>
         */

        XmlReader.Element atlasElem = XmlHelpers.loadAndValidate(compRoot, "AtlasFile");
        String filepath = atlasElem.getText();

        XmlReader.Element animSpeedElem = XmlHelpers.loadAndValidate(compRoot, "AnimationSpeed");
        float animSpeed = Float.parseFloat(animSpeedElem.getText());

        XmlReader.Element animTypeElem = compRoot.getChildByName("AnimationType");
        String animTypeResolve = animTypeElem.getText();

        int animType = Animation.NORMAL;
        if(animTypeElem != null && !animTypeResolve.isEmpty())
        {
            if(animTypeResolve.equalsIgnoreCase("Looping"))
                animType = Animation.LOOP;
            else if(animTypeResolve.equalsIgnoreCase("Reversed"))
                animType = Animation.REVERSED;
            else if(animTypeResolve.equalsIgnoreCase("Random"))
                animType = Animation.LOOP_RANDOM;
        }


        // Regions
        XmlReader.Element regionNameElem = compRoot.getChildByName("RegionNames");
        Array<String> regions = new Array<String>();


        for(XmlReader.Element regionElem : regionNameElem.getChildrenByName("Region"))
        {
            String name = regionNameElem.getAttribute("name", "");

            if(!name.isEmpty())
                regions.add(name);
        }

        // Load texture atlas
        TextureAtlas atlas = new TextureAtlas(filepath);

        // Create animation
        animation = AnimUtils.createAnimation(animSpeed, animType, atlas, regions);
    }
}
