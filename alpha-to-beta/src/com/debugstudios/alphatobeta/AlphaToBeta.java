/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta;

import com.debugstudios.alphatobeta.screens.PlayScreen;
import com.debugstudios.framework.Game;
import com.debugstudios.framework.screens.GameScreen;

public class AlphaToBeta extends Game
{
    @Override
    public GameScreen getStartScreen()
    {
        return new PlayScreen(this);
    }
}
