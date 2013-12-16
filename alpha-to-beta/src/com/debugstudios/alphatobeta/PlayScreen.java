package com.debugstudios.alphatobeta;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import com.debugstudios.alphatobeta.framework.Game;
import com.debugstudios.alphatobeta.framework.graphics.Camera;
import com.debugstudios.alphatobeta.framework.graphics.DebugRenderer;
import com.debugstudios.alphatobeta.framework.screens.GameScreen;
import com.debugstudios.alphatobeta.framework.tilemap.TileMap;
import com.debugstudios.alphatobeta.models.Player;

/**
 * Created by slacker on 12/7/13.
 */
public class PlayScreen implements GameScreen
{
    private TileMap tileMap;
    private Camera camera;

    private Player player;
    private SpriteBatch spriteBatch;

    private DebugRenderer debugRenderer;

    private int[] backgroundLayers;
    private int[] foregroundLayers;

    private final float WORLD_WIDTH = 480;
    private final float WORLD_HEIGHT = 360;

    World world;

    public PlayScreen(Game game)
    {
        Assets.load();

        camera = new Camera(WORLD_WIDTH, WORLD_HEIGHT);


        tileMap = new TileMap(Assets.map);
        tileMap.setCamera(camera);

        spriteBatch = tileMap.getSpriteBatch();

        debugRenderer = new DebugRenderer(camera);
        debugRenderer.loadFont("fonts/debugFont.fnt", "fonts/debugFont.png");

        world = new World(tileMap);

        // Index 1 is the collision index
        player = world.player;

        camera.setTarget(player);

        Gdx.gl.glClearColor(135.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1);
    }

    @Override
    public void handleInput()
    {
        world.handleInput();

        if(Gdx.input.isKeyPressed(Input.Keys.CONTROL_LEFT))
            camera.addZoom(0.1f);
        else if(Gdx.input.isKeyPressed(Input.Keys.SHIFT_LEFT))
            camera.addZoom(-0.1f);
    }

    @Override
    public void update(float delta)
    {
        world.update(delta);
    }

    @Override
    public void draw()
    {
        Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);

        // Update orthos and whatnot
        camera.update();

        tileMap.draw();

        spriteBatch.begin();
            if(player.velocity.x > 0)
                spriteBatch.draw(Assets.runRightAnimation.getKeyFrame(player.getStateTime()), player.position.x, player.position.y,
                        player.width, player.height);
            else if(player.velocity.x < 0)
                spriteBatch.draw(Assets.runLeftAnimation.getKeyFrame(player.getStateTime()), player.position.x, player.position.y,
                        player.width, player.height);
            else
                spriteBatch.draw(Assets.idleAnimation.getKeyFrame(player.getStateTime()), player.position.x, player.position.y,
                        player.width, player.height);

            debugRenderer.drawFont(spriteBatch, "Velocity X: " + player.velocity.x, 0, 0);
            debugRenderer.drawFont(spriteBatch, "Velocity Y: " + player.velocity.y, 0, debugRenderer.getFontHeight());
        spriteBatch.end();

        debugRenderer.begin();
        debugRenderer.draw(player, Color.RED, Color.BLUE);
        debugRenderer.end();
    }

    @Override
    public void pause()
    {
    }

    @Override
    public void resume()
    {
        Gdx.gl.glClearColor(135.f/255.f, 206.f/255.f, 235.f/255.f, 1);
    }

    @Override
    public void dispose()
    {
        tileMap.dispose();
        Assets.unload();
        debugRenderer.dispose();
    }

    @Override
    public void resize(int width, int height)
    {
    }
}
