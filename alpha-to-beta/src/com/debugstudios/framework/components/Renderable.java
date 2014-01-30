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

import com.badlogic.gdx.Files;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.utils.XmlReader;
import com.debugstudios.framework.parsers.XmlHelpers;


/**
 * Created by Antonis Kalou on 1/29/14.
 */
// TODO: Use textureloader
public class Renderable extends ParsedComponent
{
    private static final String TAG = Renderable.class.getSimpleName();

    public Texture texture;
    public boolean flipX = false;
    public boolean flipY = false;

    public Renderable()
    {
        texture = null;
    }

    public Renderable(String internalTextureFile)
    {
        texture = new Texture(internalTextureFile);
    }

    public Renderable(FileHandle textureFile)
    {
        texture = new Texture(textureFile);
    }


    @Override
    public void load(XmlReader.Element compRoot)
    {
        /**
         * XML File will be as such:
         *
         * <Component type="com.debugstudios.framework.components.Renderable">
         *     <!-- Will resolve to internal file by default -->
         *     <TextureFile type="internal">path/to/file.png</TextureFile>
         *     <!-- Optional, all false by default -->
         *     <Flip x="false" y="true" />
         * </Component>
         */

        XmlReader.Element textureFileElem = XmlHelpers.loadAndValidate(compRoot, "TextureFile");

        // Get file to load
        String fileName = textureFileElem.getText();

        // Attempt to access type
        String fileTypeResolve = textureFileElem.getAttribute("type");

        // Internal by default
        Files.FileType fileType= Files.FileType.Internal;
        if(!fileTypeResolve.isEmpty())
        {
            // File type provided
            if(fileTypeResolve.equalsIgnoreCase("external"))
                fileType = Files.FileType.External;
            else if(fileTypeResolve.equalsIgnoreCase("absolute"))
                fileType = Files.FileType.Absolute;
            else
                Gdx.app.error(TAG, "Unrecognised file type: " + fileTypeResolve);
        }

        texture = new Texture(Gdx.files.getFileHandle(fileName, fileType));

        // Flip args
        XmlReader.Element flipElem = compRoot.getChildByName("Flip");
        if(flipElem != null)
        {
            flipX = flipElem.getBooleanAttribute("x", false);
            flipY = flipElem.getBooleanAttribute("y", false);
        }
    }
}
