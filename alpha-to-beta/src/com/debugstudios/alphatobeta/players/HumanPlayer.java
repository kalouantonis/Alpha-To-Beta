package com.debugstudios.alphatobeta.players;

import com.debugstudios.alphatobeta.Assets;

/**
 * Created by Slacker on 17/12/13.
 */
public class HumanPlayer extends Player
{
    public HumanPlayer(float x, float y)
    {
        super(x, y, Assets.HumanPlayer.textureWidth, Assets.HumanPlayer.textureHeight);

        // Will assume already loaded
        runLeftAnimation = Assets.HumanPlayer.runLeftAnimation;
        runRightAnimation = Assets.HumanPlayer.runRightAnimation;
        idleAnimation = Assets.HumanPlayer.idleAnimation;
    }
}
