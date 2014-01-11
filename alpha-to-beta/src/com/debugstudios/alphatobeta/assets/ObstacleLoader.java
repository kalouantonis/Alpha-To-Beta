/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 1 2014
 */

package com.debugstudios.alphatobeta.assets;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.debugstudios.alphatobeta.obstacles.Obstacle;
import com.debugstudios.alphatobeta.obstacles.ObstacleBuilder;
import com.debugstudios.alphatobeta.obstacles.ObstacleFactory;
import com.debugstudios.framework.parsers.AbstractLoader;
import com.debugstudios.framework.parsers.SAXFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import java.io.IOException;
import java.nio.file.*;

/**
 * Created by Antonis Kalou on 05/01/14.
 */
public class ObstacleLoader extends AbstractLoader
{
    private ObstacleFactory factory;

    String id;

    boolean inPhysics;
    float width;
    float height;
    float mass;

    boolean inDamage;
    float damage;

    boolean inSlowdown;
    float slowdown;


    public void load(String internalFile, ObstacleFactory factory)
    {
        this.factory = factory;
        this.factory.clearObstacleBuilders();

        try
        {
            SAXParser parser = SAXFactory.getInstance().createParser();

            parser.parse(Gdx.files.internal(internalFile).path(), this);
        } catch (SAXException e)
        {
            e.printStackTrace();
        } catch (ParserConfigurationException e)
        {
            e.printStackTrace();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public void loadDirectory(String dirPath, ObstacleFactory factory, boolean recursive)
    {
        this.factory = factory;
        this.factory.clearObstacleBuilders();

        // Lazy initialization, so that it can be closed in final clause
        // Wont worry about final too much, I don't use it very often
        DirectoryStream<Path> stream = null;

        try
        {
            SAXParser parser = SAXFactory.getInstance().createParser();

            // Get all files in directory
            Path dir = Paths.get(dirPath);
            stream = Files.newDirectoryStream(dir, "*.xml");

            for(Path entry : stream)
            {
                parser.parse(entry.toFile(), this);
            }

        } catch (SAXException e)
        {
            e.printStackTrace();
        } catch (ParserConfigurationException e)
        {
            e.printStackTrace();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            if(stream != null)
            {
                try
                {
                    stream.close();
                } catch (IOException ignored)
                {
                }
            }
        }
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException
    {
        if(qName.equalsIgnoreCase("Property"))
        {
            id = String.valueOf(attributes.getValue("name"));
        }
        else if(qName.equalsIgnoreCase("Physics"))
        {
            inPhysics = true;

            width = Float.valueOf(attributes.getValue("width"));
            height = Float.valueOf(attributes.getValue("height"));
        }
        else if(qName.equalsIgnoreCase("Damage"))
        {
            inDamage = true;
        }
        else if(qName.equalsIgnoreCase("Slowdown"))
        {
            inSlowdown = true;
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException
    {
        if(qName.equalsIgnoreCase("Physics"))
        {
            inPhysics = false;
        }
        else if(qName.equalsIgnoreCase("Damage"))
        {
            inDamage = false;
        }
        else if(qName.equalsIgnoreCase("Slowdown"))
        {
            inSlowdown = false;
        }
        else if(qName.equalsIgnoreCase("Obstacle"))
        {
            factory.addObstacleBuilder(id, new ObstacleBuilder()
            {
                @Override
                public Obstacle create(float x, float y)
                {
                    Obstacle obstacle = new Obstacle(x, y, width, height);
                    obstacle.damage = damage;
                    obstacle.slowdown = slowdown;
                    obstacle.mass = mass;

                    return obstacle;
                }
            });
        }
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException
    {
        if(inPhysics)
        {
            mass = Float.parseFloat(String.valueOf(ch, start, length));
        }
        else if(inDamage)
        {
            damage = Float.parseFloat(String.valueOf(ch, start, length));
        }
        else if(inSlowdown)
        {
            slowdown = Float.parseFloat(String.valueOf(ch, start, length));
        }
    }
}
