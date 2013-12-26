/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.assets;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.maps.tiled.TmxMapLoader;
import com.debugstudios.framework.parsers.SAXFactory;
import com.debugstudios.framework.parsers.SchemaValidator;
import com.debugstudios.framework.tilemap.TileMap;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.XMLConstants;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import java.io.IOException;

/**
 * Created by Antonis Kalou on 26/12/13.
 */
public class MapLoader extends DefaultHandler
{
    private static final String TAG = MapLoader.class.getSimpleName();

    private SchemaValidator schemaValidator;
    private static final String SCHEMA_FILE = "schemas/MapSchema.xml";

    private TmxMapLoader tiledMapLoader;
    private TileMap map;

    private boolean inFilePath;

    private String prevFile = null;

    public MapLoader()
    {
        try
        {
            schemaValidator = new SchemaValidator(XMLConstants.W3C_XML_SCHEMA_NS_URI, SCHEMA_FILE);
        } catch (SAXException e)
        {
            e.printStackTrace();
        }
    }

    public void load(String internalFile, TileMap map)
    {
        prevFile = internalFile;

        this.map = map;
        this.tiledMapLoader = new TmxMapLoader();

        try
        {
            SAXParser parser = SAXFactory.getInstance().createParser();

            schemaValidator.validate(internalFile);

            parser.parse(internalFile, this);

            Gdx.app.debug(TAG, "XML File loading successful: " + internalFile);
        } catch (SAXException e)
        {
            Gdx.app.error(TAG, "Parser failed to be created:\n\t" + e.getLocalizedMessage());
        } catch (ParserConfigurationException e)
        {
            e.printStackTrace();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public void reload(TileMap map)
    {
        if(prevFile == null)
            throw new RuntimeException("Calling reload before calling load");

        load(prevFile, map);
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException
    {
        if(qName.equalsIgnoreCase("Layer"))
        {
            map.addLayer(Integer.parseInt(attributes.getValue("level")),
                    Integer.parseInt(attributes.getValue("index")));
        }
        else if(qName.equalsIgnoreCase("FilePath"))
        {
            inFilePath = true;
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException
    {
        if(qName.equalsIgnoreCase("FilePath"))
        {
            inFilePath = false;
        }
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException
    {
        if(inFilePath)
        {
            map.setInternalTileMap(tiledMapLoader.load(String.valueOf(ch, start, length)));
        }
    }

}
