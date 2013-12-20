/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.players;

import com.debugstudios.alphatobeta.Assets;

/**
 * Created by Slacker on 17/12/13.
 *
 * @author Antonis Kalou
 */
public class HumanPlayer extends Player
{
    public HumanPlayer(float x, float y)
    {
        super(x, y, Assets.map.getTileWidth(), Assets.map.getTileHeight());

        // Will assume already loaded
        /*runLeftAnimation = Assets.HumanPlayer.runLeftAnimation;
        runRightAnimation = Assets.HumanPlayer.runRightAnimation;
        idleAnimation = Assets.HumanPlayer.idleAnimation;*/
    }
}
