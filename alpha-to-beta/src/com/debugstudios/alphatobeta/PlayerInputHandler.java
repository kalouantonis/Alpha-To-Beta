package com.debugstudios.alphatobeta;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;
import com.debugstudios.alphatobeta.framework.graphics.Camera;
import com.debugstudios.alphatobeta.models.Player;

/**
 * Created by Slacker on 16/12/13.
 */
// TODO: Have these in multiplexer so that we have seperate implementations for Android and Desktop
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
            player.velocity.x = Player.MOVE_VELOCITY;
        else if(keycode == Input.Keys.A)
            player.velocity.x = -Player.MOVE_VELOCITY;

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
        float halfWidth = Gdx.graphics.getWidth() / 2;

        if(screenX > halfWidth)
            player.velocity.x = Player.MOVE_VELOCITY;
        else if(screenX < halfWidth)
            player.velocity.x = -Player.MOVE_VELOCITY;

        return true;
    }

    @Override
    public boolean touchUp(int screenX, int screenY, int pointer, int button)
    {
        player.velocity.x = 0;

        return false;
    }

    @Override
    public boolean touchDragged(int screenX, int screenY, int pointer)
    {
        if(screenY < Gdx.graphics.getHeight() / 2)
            player.jump();

        return true;
    }

    @Override
    public boolean mouseMoved(int screenX, int screenY)
    {
        return false;
    }

    @Override
    public boolean scrolled(int amount)
    {
        // Allow zooming out

        return false;
    }
}
