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

package com.debugstudios.framework.entities;


import com.badlogic.gdx.Files;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.utils.XmlReader;
import com.debugstudios.framework.components.ParsedComponent;

import java.io.IOException;

/**
 * Created by Antonis Kalou on 1/30/14.
 */
public class ParsedEntity extends ashley.core.Entity
{
    private static final String TAG = ParsedEntity.class.getSimpleName();

    public void load(String filePath, Files.FileType fileType)
    {

        try
        {
            FileHandle xmlFile = Gdx.files.getFileHandle(filePath, fileType);

            XmlReader xml = new XmlReader();
            XmlReader.Element root = xml.parse(xmlFile);

            for(XmlReader.Element element : root.getChildrenByName("Component"))
            {
                String compClass = element.getAttribute("type");
                if(compClass == null)
                    throw new RuntimeException("Could not load '" + filePath + "' - No type defined");

                try
                {
                    // Create new parsed component from class name
                    ParsedComponent component = (ParsedComponent)Class.forName(compClass).newInstance();
                    // Load using element
                    component.load(element);

                    // Add component to entity
                    this.add(component);

                } catch (ClassNotFoundException e)
                {
                    Gdx.app.error(TAG, "Could not load component, invalid type: " + compClass);
                } catch (InstantiationException e)
                {
                    e.printStackTrace();
                } catch (IllegalAccessException e)
                {
                    e.printStackTrace();
                }
            }
        }
        catch (IOException e)
        {
            Gdx.app.error(TAG, "Could not load entity from xml: " + filePath + "\n\t" + e.getMessage());
        }
    }
}
