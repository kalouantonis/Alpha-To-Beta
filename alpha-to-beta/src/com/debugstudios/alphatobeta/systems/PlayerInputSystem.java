/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 2 2014
 */

package com.debugstudios.alphatobeta.systems;

import ashley.core.Engine;
import ashley.core.Entity;
import ashley.core.EntitySystem;
import ashley.core.Family;
import ashley.utils.IntMap;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.debugstudios.alphatobeta.components.PlayerInputComponent;
import com.debugstudios.framework.components.Physics;
import com.debugstudios.framework.components.Transform;

/**
 * Created by slacker on 2/1/14.
 */
public class PlayerInputSystem extends EntitySystem
{
    IntMap<Entity> entities;
    Family family;

    public PlayerInputSystem()
    {
        this(0);
    }

    public PlayerInputSystem(int priority)
    {
        super(priority);

        entities = new IntMap<Entity>();
        family = Family.getFamilyFor(Physics.class, PlayerInputComponent.class);
    }

    @Override
    public void addedToEngine(Engine engine)
    {
        entities = engine.getEntitiesFor(family);

        for (Entity entity : entities.values())
        {
            // Load input if not already loaded
            if (!entity.getComponent(PlayerInputComponent.class).inputLoaded)
            {
                Physics physics = entity.getComponent(Physics.class);
                final Vector2 velocity = physics.velocity;

                Gdx.input.setInputProcessor(new InputProcessor()
                {
                    @Override
                    public boolean keyDown(int keycode)
                    {
                        if (keycode == Input.Keys.D || keycode == Input.Keys.RIGHT)
                            velocity.x = 100;
                        else if (keycode == Input.Keys.A || keycode == Input.Keys.LEFT)
                            velocity.x = -100;

                        return true;
                    }

                    @Override
                    public boolean keyUp(int keycode)
                    {

                        if(keycode == Input.Keys.A || keycode == Input.Keys.D ||
                                keycode == Input.Keys.LEFT || keycode == Input.Keys.RIGHT)
                            velocity.x = 0;

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
                });

                entity.getComponent(PlayerInputComponent.class).inputLoaded = true;
            }
        }

    }

    @Override
    public void removedFromEngine(Engine engine)
    {
        super.removedFromEngine(engine);
    }
}
