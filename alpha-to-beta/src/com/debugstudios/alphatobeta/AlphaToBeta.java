package com.debugstudios.alphatobeta;

import com.debugstudios.alphatobeta.framework.Game;
import com.debugstudios.alphatobeta.framework.screens.GameScreen;

public class AlphaToBeta extends Game
{
    @Override
    public GameScreen getStartScreen()
    {
        return new PlayScreen(this);
    }
}
