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

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.utils.XmlReader;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.framework.parsers.XmlHelpers;
import com.debugstudios.framework.parsers.XmlReaderException;

/**
 * Created by Antonis Kalou on 1/29/14.
 */
public class CameraComponent extends ParsedComponent
{
    public Camera camera;

    public CameraComponent()
    {
        camera = new Camera();
    }

    public CameraComponent(float viewportWidth, float viewportHeight)
    {
        camera = new Camera(viewportWidth, viewportHeight);
    }

    @Override
    public void load(XmlReader.Element compRoot) throws XmlReaderException
    {
        /**
         * XML defined as such:
         *
         * <Component type="com.debugstudios.framework.components.CameraComponent">
         *     <Viewport width="200" height="200" />
         * </Component>
         */

        XmlReader.Element viewportElem = XmlHelpers.loadAndValidate(compRoot, "Viewport");

        camera.viewportWidth = viewportElem.getFloatAttribute("width", Gdx.graphics.getWidth());
        camera.viewportHeight = viewportElem.getFloatAttribute("height", Gdx.graphics.getHeight());
    }
}
