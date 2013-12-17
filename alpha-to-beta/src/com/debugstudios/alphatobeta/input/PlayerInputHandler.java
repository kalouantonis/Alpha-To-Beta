package com.debugstudios.alphatobeta.input;

import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.alphatobeta.players.Player;

/**
 * Created by Slacker on 16/12/13.
 */
// TODO: Have these in multiplexer so that we have separate implementations for Android and Desktop
// TODO: Also, use GestureListener for android impl
public class PlayerInputHandler implements InputProcessor
{
    Player player;
    Camera camera;

    public PlayerInputHandler(Camera camera, Player player)
    {
        this.player = player;
        this.camera = camera;
    }

    @Override
    public boolean keyDown(int keycode)
    {
        if(keycode == Input.Keys.D || keycode == Input.Keys.RIGHT)
            player.velocity.x = player.MOVE_VELOCITY;
        else if(keycode == Input.Keys.A || keycode == Input.Keys.LEFT)
            player.velocity.x = -player.MOVE_VELOCITY;

        if(keycode == Input.Keys.SPACE
                || keycode == Input.Keys.UP || keycode == Input.Keys.W)
            player.jump();

        return true;
    }

    @Override
    public boolean keyUp(int keycode)
    {
        if(keycode == Input.Keys.A || keycode == Input.Keys.D ||
                 keycode == Input.Keys.LEFT || keycode == Input.Keys.RIGHT)
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
        player.velocity.x = 0;

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
