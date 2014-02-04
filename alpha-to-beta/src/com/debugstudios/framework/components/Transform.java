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

import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.utils.XmlReader;
import com.debugstudios.framework.parsers.XmlHelpers;
import com.debugstudios.framework.parsers.XmlReaderException;

/**
 * Created by Antonis Kalou on 1/29/14.
 */
public class Transform extends ParsedComponent
{
    // TODO: Make position Vector3 so as to use Z for layering
    public Rectangle transform;
    public float z = 0f;
    public Vector2 origin;
    public float rotation;
    public Vector2 scale;

    public Transform()
    {
        this(0, 0, 1, 1);
    }

    public Transform(float x, float y, float width, float height)
    {
        this.transform = new Rectangle(x, y, width, height);
        this.origin = new Vector2(width / 2, height / 2);

        this.scale = new Vector2(1f, 1f);
        this.rotation = 0;
    }

    public Transform(Vector2 position, Vector2 bounds)
    {
        this(position.x, position.y, bounds.x, bounds.y);
    }

    public Transform(Rectangle transform)
    {
        this(transform.x, transform.y, transform.width, transform.height);
    }

    @Override
    public void load(XmlReader.Element compRoot) throws XmlReaderException
    {
        /**
         * XML Defined as such:
         *
         * <Component type="com.debugstudios.framework.Transform">
         *      <!-- Not tile coordinates, Z is optional, set to 0 by default  -->
         *      <Transform x="0" y="0" z="10" width="16" height="16" />
         *      <!-- Optional. If not provided, x and y are taken by half of bounds -->
         *      <Origin x="8" y="8" />
         *      <!-- Optional. Set to 0 by default -->
         *      <Rotation>120</Rotation>
         *      <!-- Optional. Set to 1 by default -->
         *      <Scale x="1" y="2" />
         * </Component>
         */

        // Transform
        XmlReader.Element transformElem = XmlHelpers.loadAndValidate(compRoot, "Transform");
        transform.x = transformElem.getFloatAttribute("x");
        transform.y = transformElem.getFloatAttribute("y");
        transform.width = transformElem.getFloatAttribute("width");
        transform.height = transformElem.getFloatAttribute("height");
        z = transformElem.getFloatAttribute("z", 0f);

        // Origin, manual validation
        XmlReader.Element originElem = compRoot.getChildByName("Origin");

        if(originElem != null)
        {
            XmlHelpers.fillVectorFromElement(originElem, origin);
        }
        else
        {
            // No origin element found, willing with half of bounds
            origin.set(transform.width / 2, transform.y / 2);
        }

        // Rotation
        XmlReader.Element rotationElem = compRoot.getChildByName("Rotation");

        if(rotationElem != null)
        {
            // Should work
            this.rotation = Float.parseFloat(rotationElem.getText());
        }
        else
        {
            // Set to 0 by default
            this.rotation = 0;
        }

        XmlReader.Element scaleElem = compRoot.getChildByName("Scale");
        if(scaleElem != null)
        {
            XmlHelpers.fillVectorFromElement(scaleElem, scale);
        }
        else
        {
            scale.set(1f, 1f);
        }
    }
}
