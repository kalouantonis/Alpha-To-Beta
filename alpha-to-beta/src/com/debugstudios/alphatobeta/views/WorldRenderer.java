package com.debugstudios.alphatobeta.views;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.debugstudios.alphatobeta.Assets;
import com.debugstudios.alphatobeta.World;
import com.debugstudios.alphatobeta.models.*;

/**
 * Created by slacker on 15/12/13.
 */
public class WorldRenderer
{
    private World world;
    private SpriteBatch batch;

    public WorldRenderer(SpriteBatch batch, World world)
    {
        this.world = world;
        this.batch = batch;
    }

    public void render()
    {
        Player player = world.player;

        batch.begin();

        batch.draw(Assets.runRightAnimation.getKeyFrame(player.getStateTime()), player.position.x, player.position.y, player.width, player.height);

        batch.end();
    }

}
