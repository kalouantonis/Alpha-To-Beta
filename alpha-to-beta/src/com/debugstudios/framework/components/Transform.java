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

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.utils.XmlReader;
import com.debugstudios.framework.parsers.XmlHelpers;

/**
 * Created by Antonis Kalou on 1/29/14.
 */
public class Transform extends ParsedComponent
{
    public Vector2 position;
    public Vector2 bounds;
    public Vector2 origin;

    public Transform(float x, float y, float width, float height)
    {
        this.position = new Vector2(x, y);
        this.bounds = new Vector2(width, height);
        this.origin = new Vector2(width / 2, height / 2);
    }

    public Transform(Vector2 position, Vector2 bounds)
    {
        this(position.x, position.y, bounds.x, bounds.y);
    }

    @Override
    public void load(XmlReader.Element compRoot)
    {
        /**
         * XML Defined as such:
         *
         * <Component type="com.debugstudios.framework.Transform">
         *      <!-- Not tile coordinates  -->
         *      <Position x="20" y="22" />
         *      <Bounds x="16" y="16" />
         *      <!-- Optional. If not provided, x and y are taken by half of bounds -->
         *      <Origin x="8" y="8" />
         * </Component>
         */

        // Position
        XmlReader.Element posElem = XmlHelpers.loadAndValidate(compRoot, "Position");
        XmlHelpers.fillVectorFromElement(posElem, position);

        // Bounds
        XmlReader.Element boundsElem = XmlHelpers.loadAndValidate(compRoot, "Bounds");
        XmlHelpers.fillVectorFromElement(boundsElem, bounds);

        // Origin, manual validation
        XmlReader.Element originElem = compRoot.getChildByName("Origin");

        if(originElem != null)
        {
            XmlHelpers.fillVectorFromElement(originElem, origin);
        }
        else
        {
            // No origin element found, willing with half of bounds
            origin.set(bounds.x / 2, bounds.y / 2);
        }
    }
}
