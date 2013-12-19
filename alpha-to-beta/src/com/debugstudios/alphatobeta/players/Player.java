/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.players;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;
import com.debugstudios.framework.gameobjects.DynamicEntity;
import com.debugstudios.framework.tilemap.CollisionLayer;

import java.sql.Date;
import java.text.ParseException;

/**
 *
 * @author Antonis Kalou
 */
public class Player extends DynamicEntity
{
    // CONSTANTS /////////////////////////////////////////////////////////////////////////
    /** Should remain the same, TODO: Move to physics.Constants */
    public static final float GRAVITY = -9.8f;
    /** Mass for F=ma calculations */
    public static final float MASS = 20;
    /** Different for every player, dictates strength. Eventually allow upgrades on this */
    public static Vector2 MAX_VELOCITY = new Vector2(200, 400);
    /** Player X movement velocity */
    public float MOVE_VELOCITY = 100;
    /** Player Y impulse velocity */
    public static float JUMP_VELOCITY = 150;
    /** Maximum allowed jumps. TODO: 1 for fatty :P */
    private static final short MAX_JUMPS = 2;
    //////////////////////////////////////////////////////////////////////////////////////

    /** Track state time, for animation and timed acceleration */
    private float stateTime = 0.f;
    /** Current number of jumps performed */
    private short numJumps = 0;

    /** Bottom collision layer, excludes objects */
    private CollisionLayer collisionLayer;
    /** Checks if x or y collision has occured */
    private boolean xCollision, yCollision;

    /** Animation data structures. */
    // TODO: Run left, idle is redundant
    public Animation runLeftAnimation = null;
    public Animation runRightAnimation = null;
    public Animation idleAnimation = null;

    public Player(float x, float y, float width, float height)
    {
        super(x, y, width, height);

        accel.y = GRAVITY * MASS;
    }

    @Override
    public void update(float deltaTime)
    {
        if(!xCollision)
            velocity.x += accel.x * deltaTime;
        if(!yCollision)
            velocity.y += accel.y * deltaTime;

        velocity.x = MathUtils.clamp(velocity.x, -MAX_VELOCITY.x, MAX_VELOCITY.x);
        velocity.y = MathUtils.clamp(velocity.y, -MAX_VELOCITY.y, MAX_VELOCITY.y);

        xCollision = false;
        yCollision = false;

        float oldX = position.x;
        float oldY = position.y;

        position.x += velocity.x * deltaTime;

        if(velocity.x > 0)
            xCollision = collisionLayer.collidesRight(this);
        else if(velocity.x < 0)
            xCollision = collisionLayer.collidesLeft(this);

        if(xCollision)
            position.x = oldX;

        position.y += velocity.y * deltaTime;

        if(velocity.y > 0)
            yCollision = collisionLayer.collidesTop(this);
        else if(velocity.y < 0)
        {
            yCollision = collisionLayer.collidesBottom(this);

            if(yCollision)
                numJumps = 0;
        }

        if(yCollision)
        {
            position.y = oldY;
            velocity.y = 0;
        }

        stateTime += deltaTime;
    }


    /**
     * Perform jump according to JUMP_VELOCITY
     */
    public void jump()
    {
        if(numJumps++ < MAX_JUMPS)
        {
            velocity.y = JUMP_VELOCITY;
        }
    }

    /**
     * Set bottom collision layer
     *
     * @param collisionLayer Collision layer for tile map
     */
    public void setCollisionLayer(CollisionLayer collisionLayer)
    {
        this.collisionLayer = collisionLayer;
    }

    /**
     * Get current state time
     *
     * @return the time the object has been in a state
     */
    public float getStateTime()
    {
        return stateTime;
    }

    /**
     * Reset state time back to 0
     */
    public void resetStateTime()
    {
        stateTime = 0.f;
    }

    /**
     * Will return the texture region of selected animation according to state time
     * @param animation Animation class used
     * @return Texture region used in current state time
     */
    public TextureRegion getAnimationFrame(Animation animation)
    {
       return animation.getKeyFrame(stateTime);
    }
}
