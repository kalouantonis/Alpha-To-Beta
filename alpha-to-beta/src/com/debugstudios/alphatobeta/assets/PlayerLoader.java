/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.assets;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.debugstudios.alphatobeta.utils.SpeedRegionPair;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.framework.graphics.AnimUtils;
import com.debugstudios.framework.parsers.SAXFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import java.io.File;
import java.io.IOException;

/**
 * Created by Antonis Kalou on 18/12/13.
 */
public class PlayerLoader extends DefaultHandler
{
    private static final String TAG = PlayerLoader.class.getSimpleName();
    private String prevFile = null;

    private Player player = null;
    private float animationSpeed = 0.f;

    private TextureAtlas playerAtlas = null;

    private SpeedRegionPair runRightPair;
    private SpeedRegionPair runLeftPair;
    private SpeedRegionPair idlePair;

    // In animation element
    private boolean inAnim = false;
    private boolean inRightAnim = false;
    private boolean inLeftAnim = false;
    private boolean inIdleAnim = false;

    private boolean inRegionName = false;

    // Physics element
    private boolean inPhysics = false;
    // Inner elements
    private boolean inMass = false;
    private boolean inJumpSpeed = false;
    private boolean inMoveSpeed = false;


    public PlayerLoader()
    {
        runLeftPair = new SpeedRegionPair();
        runRightPair = new SpeedRegionPair();
        idlePair = new SpeedRegionPair();
    }

    // Load from XML, set textures, and bounds and physics
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

            parser.parse(new File(internalFile), this);
        }
        catch (SAXException e)
        {
            Gdx.app.error(TAG, "Parser failed to be created:\n" + e.getMessage());
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
                runLeftPair.setSpeed(Float.parseFloat(attributes.getValue("speed")));

                inLeftAnim = true;
            }
            else if(qName.equalsIgnoreCase("right"))
            {
                runRightPair.setSpeed(Float.parseFloat(attributes.getValue("speed")));

                inRightAnim = true;
            }
            else if(qName.equalsIgnoreCase("idle"))
            {
                idlePair.setSpeed(Float.parseFloat(attributes.getValue("speed")));

                inIdleAnim = true;
            }
            else if(qName.equalsIgnoreCase("regionName"))
            {
                inRegionName = true;
            }
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
                player.runLeftAnimation = AnimUtils.createLoopAnimation(runLeftPair.getSpeed(), playerAtlas,
                        runLeftPair.getRegions());

                inLeftAnim = false;
            }
            else if(qName.equalsIgnoreCase("right"))
            {
                player.runRightAnimation = AnimUtils.createLoopAnimation(runRightPair.getSpeed(), playerAtlas,
                        runRightPair.getRegions());

                inRightAnim = false;
            }
            else if(qName.equalsIgnoreCase("idle"))
            {
                player.idleAnimation = AnimUtils.createLoopAnimation(idlePair.getSpeed(), playerAtlas,
                        idlePair.getRegions());

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
            if(inRegionName)
            {
                if(inRightAnim)
                {
                    runRightPair.addRegion(new String(ch, start, length));
                }
                else if(inLeftAnim)
                {
                    runLeftPair.addRegion(new String(ch, start, length));
                }
                else if(inIdleAnim)
                {
                    idlePair.addRegion(new String(ch, start, length));
                }
            }
        }

        if(inPhysics)
        {
            if(inMass)
            {
                player.setMass(Float.parseFloat(new String(ch, start, length)));
                inMass = false;
            }
            else if(inJumpSpeed)
            {
                player.JUMP_VELOCITY = Float.parseFloat(new String(ch, start, length));
                inJumpSpeed = false;
            }
            else if(inMoveSpeed)
            {
                player.MOVE_VELOCITY = Float.parseFloat(new String(ch, start, length));
                inMoveSpeed = false;
            }
        }
    }
}
