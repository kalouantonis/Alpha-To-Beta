package com.debugstudios.alphatobeta;

import com.debugstudios.framework.Game;
import com.debugstudios.framework.screens.GameScreen;
import com.debugstudios.alphatobeta.screens.PlayScreen;

public class AlphaToBeta extends Game
{
    @Override
    public GameScreen getStartScreen()
    {
        return new PlayScreen(this);
    }
}
