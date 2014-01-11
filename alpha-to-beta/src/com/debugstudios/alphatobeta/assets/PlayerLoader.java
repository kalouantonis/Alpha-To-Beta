/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.assets;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.alphatobeta.utils.SpeedRegionPair;
import com.debugstudios.framework.graphics.AnimUtils;
import com.debugstudios.framework.parsers.AbstractLoader;
import com.debugstudios.framework.parsers.SAXFactory;
import com.debugstudios.framework.parsers.SchemaValidator;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.XMLConstants;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import java.io.IOException;

/**
 * Created by Antonis Kalou on 18/12/13.
 */
public class PlayerLoader extends AbstractLoader
{
    /** Tag to use for logging */
    private static final String TAG = PlayerLoader.class.getSimpleName();

    /** Store previous file for reloading */
    private String prevFile = null;

    /** Used to validate XML file */
    private SchemaValidator schemaValidator;
    /** Default schema file */
    private static final String SCHEMA_FILE = "schemas/PlayerSchema.xml";

    /** Player to load */
    private Player player = null;

    /** Atlas to get texture regions from */
    private TextureAtlas playerAtlas = null;

    /** Pair of regions and speeds */
    private SpeedRegionPair speedRegionPair;
//    private Animation currAnimation = null;

    // In animation element
    private boolean inAnim = false;
    private boolean inRightAnim = false;
    private boolean inLeftAnim = false;
    private boolean inIdleAnim = false;
    private int currAnimLoop = Animation.NORMAL;

    private boolean inRegionName = false;

    // Physics element
    private boolean inPhysics = false;
    // Inner elements
    private boolean inMass = false;
    private boolean inJumpSpeed = false;
    private boolean inMoveSpeed = false;


    /**
     * Create new loader instance
     */
    public PlayerLoader()
    {
        speedRegionPair = new SpeedRegionPair();

        try
        {
            schemaValidator = new SchemaValidator(XMLConstants.W3C_XML_SCHEMA_NS_URI, SCHEMA_FILE);
        }
        catch (SAXException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Load player attributes from XML File
     *
     * @param internalFile XML File to load from
     * @param player       Player reference to load in to
     * @param playerAtlas  Texture atlas to get regions from
     */
    public void load(String internalFile, Player player, TextureAtlas playerAtlas)
    {
        // Store previous file, for use when reloading
        prevFile = internalFile;

        this.player = player;
        this.playerAtlas = playerAtlas;

        try
        {
            // Create SAXParser object
            SAXParser parser = SAXFactory.getInstance().createParser();

            schemaValidator.validate(internalFile);

            parser.parse(Gdx.files.internal(internalFile).file(), this);

            Gdx.app.debug(TAG, "XML File loading successful: " + internalFile);
        }
        catch (SAXException e)
        {
            Gdx.app.error(TAG, "Parser failed to be created:\n\t" + e.getLocalizedMessage());
        }
        catch (ParserConfigurationException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Reload player data, using previously loaded data.
     * This includes the texture atlas and xml source.
     *
     * @param player Player reference to load in to
     */
    public void reload(Player player)
    {
        if(this.prevFile == null || this.playerAtlas == null)
            throw new RuntimeException("Calling reload before calling load");

        load(prevFile, player, playerAtlas);
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException
    {
        if(qName.equalsIgnoreCase("Animation"))
        {
            inAnim = true;
        }
        else if(inAnim)
        {
            // Add to regions according to XML defs
            if(qName.equalsIgnoreCase("left"))
            {
//                currAnimation = player.runLeftAnimation;
                inLeftAnim = true;

                currAnimLoop = Boolean.parseBoolean(attributes.getValue("looping"))
                                ? Animation.LOOP
                                : Animation.NORMAL;
            }
            else if(qName.equalsIgnoreCase("right"))
            {
//                currAnimation = player.runRightAnimation;
                inRightAnim = true;

                currAnimLoop = Boolean.parseBoolean(attributes.getValue("looping"))
                        ? Animation.LOOP
                        : Animation.NORMAL;
            }
            else if(qName.equalsIgnoreCase("idle"))
            {
//                currAnimation = player.idleAnimation;
                inIdleAnim = true;

                currAnimLoop = Boolean.parseBoolean(attributes.getValue("looping"))
                        ? Animation.LOOP
                        : Animation.NORMAL;
            }
            else if(qName.equalsIgnoreCase("regionName"))
                inRegionName = true;

            if((!inRegionName) && (inLeftAnim || inRightAnim || inIdleAnim))
                speedRegionPair.setSpeed(Float.parseFloat(attributes.getValue("interval")));

        }
        else if(qName.equalsIgnoreCase("Physics"))
        {
            inPhysics = true;
        }
        else if(inPhysics)
        {
            if(qName.equalsIgnoreCase("mass"))
                inMass = true;
            else if(qName.equalsIgnoreCase("jump_speed"))
                inJumpSpeed = true;
            else if(qName.equalsIgnoreCase("move_speed"))
                inMoveSpeed = true;
            else if(qName.equalsIgnoreCase("max_velocity"))
            {
                player.MAX_VELOCITY.x = Float.parseFloat(attributes.getValue("x"));
                player.MAX_VELOCITY.y = Float.parseFloat(attributes.getValue("y"));
            }
        }
        else if(qName.equalsIgnoreCase("Texture"))
        {
            // Store width and height attributes
            player.width = Float.parseFloat(attributes.getValue("width"));
            player.height = Float.parseFloat(attributes.getValue("height"));
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException
    {

        if(qName.equalsIgnoreCase("Animation"))
        {
            inAnim = false;
        }
        else if(inAnim)
        {
            if(qName.equalsIgnoreCase("left"))
            {
                player.runLeftAnimation = AnimUtils.createAnimation(speedRegionPair.getSpeed(), currAnimLoop,
                        playerAtlas, speedRegionPair.getRegions());
                speedRegionPair.clear();

                inLeftAnim = false;
            }
            else if(qName.equalsIgnoreCase("right"))
            {
                player.runRightAnimation = AnimUtils.createAnimation(speedRegionPair.getSpeed(), currAnimLoop,
                        playerAtlas, speedRegionPair.getRegions());
                speedRegionPair.clear();

                inRightAnim = false;
            }
            else if(qName.equalsIgnoreCase("idle"))
            {
                player.idleAnimation = AnimUtils.createAnimation(speedRegionPair.getSpeed(), currAnimLoop,
                        playerAtlas, speedRegionPair.getRegions());
                speedRegionPair.clear();

                inIdleAnim = false;
            }
            else if(qName.equalsIgnoreCase("regionName"))
            {
                inRegionName = false;
            }
        }
        else if(qName.equalsIgnoreCase("Physics"))
        {
            inPhysics = false;
        }
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException
    {
        if(inAnim)
        {
            if(inRegionName && (inLeftAnim || inRightAnim || inIdleAnim))
            {
                speedRegionPair.addRegion(String.valueOf(ch, start, length));
            }
        }

        if(inPhysics)
        {
            if(inMass)
            {
                player.setMass(Float.parseFloat(String.valueOf(ch, start, length)));
                inMass = false;
            }
            else if(inJumpSpeed)
            {
                player.JUMP_VELOCITY = Float.parseFloat(String.valueOf(ch, start, length));
                inJumpSpeed = false;
            }
            else if(inMoveSpeed)
            {
                player.MOVE_VELOCITY = Float.parseFloat(String.valueOf(ch, start, length));
                inMoveSpeed = false;
            }
        }
    }
}
