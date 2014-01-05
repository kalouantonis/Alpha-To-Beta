/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.renderers;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.debugstudios.alphatobeta.World;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.framework.graphics.DebugRenderer;

/**
 * Created by Slacker on 17/12/13.
 */
public class WorldDebugRenderer
{
    private static final String FONT_NAME = "debugFont";

    DebugRenderer renderer;
    World world;
    SpriteBatch batch;

    public WorldDebugRenderer(Camera camera, SpriteBatch batch, World world)
    {
        this.renderer = new DebugRenderer(camera);

        this.batch = batch;
        this.world = world;

        // Will assume that all fonts are stored in the fonts directory
        renderer.loadFont("fonts/" + FONT_NAME + ".fnt", "fonts/" + FONT_NAME + ".png");
    }

    public void render()
    {
        // Draw fonts
        batch.begin();
            renderDebugInfo();
        batch.end();

        renderer.begin();
            renderPlayerDebug(world.player);
        renderer.end();
    }

    private void renderDebugInfo()
    {
        Player player = world.player;

        renderer.drawFont(batch, "Velocity X: " + player.velocity.x, 0, 0);
        renderer.drawFont(batch, "Velocity Y: " + player.velocity.y, 0, renderer.getFontHeight());
    }

    private void renderPlayerDebug(Player player)
    {
        renderer.draw(player, Color.RED, Color.BLUE);
    }

    public void dispose()
    {
        renderer.dispose();
    }
}
