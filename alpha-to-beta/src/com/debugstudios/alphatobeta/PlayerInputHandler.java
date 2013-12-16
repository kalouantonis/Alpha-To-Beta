package com.debugstudios.alphatobeta;

import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;
import com.debugstudios.alphatobeta.models.Player;

/**
 * Created by Slacker on 16/12/13.
 */
public class PlayerInputHandler implements InputProcessor
{
    Player player;

    public PlayerInputHandler(Player player)
    {
       this.player = player;
    }

    @Override
    public boolean keyDown(int keycode)
    {
        if(keycode == Input.Keys.D)
            player.velocity.x = 100;
        else if(keycode == Input.Keys.A)
            player.velocity.x = -100;

        if(keycode == Input.Keys.SPACE)
            player.jump();

        return true;
    }

    @Override
    public boolean keyUp(int keycode)
    {
        if(keycode == Input.Keys.A || keycode == Input.Keys.D)
            player.velocity.x = 0;

        return true;
    }

    @Override
    public boolean keyTyped(char character)
    {
        return false;
    }

    @Override
    public boolean touchDown(int screenX, int screenY, int pointer, int button)
    {
        return false;
    }

    @Override
    public boolean touchUp(int screenX, int screenY, int pointer, int button)
    {
        return false;
    }

    @Override
    public boolean touchDragged(int screenX, int screenY, int pointer)
    {
        return false;
    }

    @Override
    public boolean mouseMoved(int screenX, int screenY)
    {
        return false;
    }

    @Override
    public boolean scrolled(int amount)
    {
        return false;
    }
}
