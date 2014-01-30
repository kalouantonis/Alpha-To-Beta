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
public class Movement extends ParsedComponent
{
    public Vector2 velocity;
    public Vector2 maxVelocity = new Vector2(100, 100);

    public Vector2 accel;

    public Movement()
    {
       velocity = new Vector2();
        accel = new Vector2();
    }

    public Movement(Vector2 velocity, Vector2 accel)
    {
        this.velocity = velocity;
        this.accel = accel;
    }

    @Override
    public void load(XmlReader.Element compRoot)
    {
        /**
         * XML Defined as such
         *
         * <Component type="com.debugstudios.framwork.components.Movement">
         *       <Velocity x="20" y="0" >
         *          <MaxVelocity x="200" y="400" />
         *       </Velocity>
         *       <Acceleration x="0" y = "-9.8" />
         * </Component>
         */
        // Velocity
        XmlReader.Element velocityElem = XmlHelpers.loadAndValidate(compRoot, "Velocity");
        XmlHelpers.fillVectorFromElement(velocityElem, velocity);

        // MaxVelocity
        XmlReader.Element maxVelElem = XmlHelpers.loadAndValidate(velocityElem, "MaxVelocity");
        XmlHelpers.fillVectorFromElement(maxVelElem, maxVelocity);

        // Acceleration
        XmlReader.Element accelElem = XmlHelpers.loadAndValidate(compRoot, "Acceleration");
        XmlHelpers.fillVectorFromElement(accelElem, accel);
    }
}
