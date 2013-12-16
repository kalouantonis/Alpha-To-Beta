package com.debugstudios.alphatobeta.models;

import android.graphics.drawable.ShapeDrawable;
import com.badlogic.gdx.graphics.g3d.Shader;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;
import com.debugstudios.alphatobeta.framework.gameobjects.DynamicEntity;
import com.debugstudios.alphatobeta.framework.tilemap.CollisionLayer;

/**
 * Created with IntelliJ IDEA.
 * User: slacker
 * Date: 11/30/13
 * Time: 4:50 PM
 * To change this template use File | Settings | File Templates.
 */
public class Player extends DynamicEntity
{
    // CONSTANTS /////////////////////////////////////////////////////////////////////////
    public static final float GRAVITY = -9.8f;
    public static final float MASS = 20;
    public static Vector2 MAX_VELOCITY = new Vector2(2.2f * 60, 400);
    public static float MOVE_VELOCITY = 100;
    public static float JUMP_VELOCITY = 150;
    private static final short MAX_JUMPS = 2;
    //////////////////////////////////////////////////////////////////////////////////////

    /** Track state time, for animation and timed acceleration */
    private float stateTime = 0.f;
    private short numJumps = 0;

    private CollisionLayer collisionLayer;
    private boolean xCollision, yCollision;


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


    public void jump()
    {
        if(numJumps++ < MAX_JUMPS)
        {
            velocity.y = JUMP_VELOCITY;
        }
    }

    public CollisionLayer getCollisionLayer()
    {
        return collisionLayer;
    }

    public void setCollisionLayer(CollisionLayer collisionLayer)
    {
        this.collisionLayer = collisionLayer;
    }

    public float getStateTime()
    {
        return stateTime;
    }
}
