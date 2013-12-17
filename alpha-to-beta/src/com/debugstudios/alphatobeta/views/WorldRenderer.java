package com.debugstudios.alphatobeta.views;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.debugstudios.alphatobeta.World;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.framework.graphics.Camera;

import javax.microedition.khronos.opengles.GL10;

/**
 * Created by slacker on 15/12/13.
 */
public class WorldRenderer
{
    private final int NUM_PLAYERS = 5;

    private World world;
    private SpriteBatch batch;
    private Camera camera;

    public WorldRenderer(Camera camera, SpriteBatch batch, World world)
    {
        this.camera = camera;
        this.batch = batch;
        this.world = world;

    }

    public void render()
    {
        // Clear screen
        Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);

        // Update projection matrix
        camera.update();

        // Tile map uses own batch
        renderTileMap();

        batch.begin();
            renderPlayers();
        batch.end();
    }

    private void renderTileMap()
    {
        // Just draw whole thing in background for now
        world.tileMap.draw();
    }

    private void renderPlayers()
    {
        for(Player player : world.players)
        {
            float xPos = player.position.x;
            float yPos = player.position.y;

            if(player.velocity.x > 0)
                batch.draw(player.getAnimationFrame(player.runRightAnimation), xPos, yPos,
                        player.width, player.height);
            else if(player.velocity.x < 0)
                batch.draw(player.getAnimationFrame(player.runLeftAnimation), xPos, yPos,
                        player.width, player.height);
            else
                batch.draw(player.getAnimationFrame(player.idleAnimation), xPos, yPos,
                        player.width, player.height);
        }



    }
}
