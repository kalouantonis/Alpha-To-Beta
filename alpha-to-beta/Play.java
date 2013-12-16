package com.me.mygdxgame;

import com.badlogic.gdx.Application;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.*;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.maps.objects.RectangleMapObject;
import com.me.mygdxgame.tilemap.CollisionLayer;
import com.me.mygdxgame.graphics.Camera;
import com.me.mygdxgame.tilemap.TileMap;


public class Play implements Screen
{
    private TileMap tileMap;
    private Camera camera;

    private Character player;
    private SpriteBatch spriteBatch;

    private int[] backgroundLayers;
    private int[] foregroundLayers;

    private final float WORLD_WIDTH = 480;
    private final float WORLD_HEIGHT = 360;

    @Override
    public void render(float delta)
    {
        GL10 gl = Gdx.graphics.getGL10();

        gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        if(Gdx.input.isKeyPressed(Input.Keys.SHIFT_LEFT))
            camera.zoom += 5 * delta;
        if(Gdx.input.isKeyPressed(Input.Keys.CONTROL_LEFT))
            camera.zoom -= 5 * delta;


        if(Gdx.input.isKeyPressed(Input.Keys.R))
            resetPlayer();

        if(Gdx.input.isKeyPressed(Input.Keys.M))
            resetMap();

        if(Gdx.input.isKeyPressed(Input.Keys.SPACE))
            player.jump(100);

        player.update(Gdx.graphics.getDeltaTime());

        camera.position.x = player.getX() + (player.getWidth() / 2);
        camera.position.y = player.getY() + (player.getHeight() / 2);

        camera.update();

        //renderer.setView(camera);
        //renderer.render(backgroundLayers);
        tileMap.drawLayers(backgroundLayers);

        spriteBatch.begin();
        player.draw(spriteBatch);
        spriteBatch.end();

        tileMap.drawLayers(foregroundLayers);
    }

    @Override
    public void resize(int width, int height)
    {
        camera.viewportWidth = WORLD_WIDTH;
        camera.viewportHeight = WORLD_HEIGHT;
    }

    @Override
    public void show()
    {
        Gdx.app.setLogLevel(Application.LOG_DEBUG);

        Gdx.gl.glClearColor(135.f/255.f, 206.f/255.f, 235.f/255.f, 1);

        camera = new Camera();
        camera.zoom = 1 / 5f;

       /* camera.viewportWidth = 100.f;
        camera.viewportHeight = 75.f;*/


        // Animated tiles /////////////////////////////////////////////////////////

        /*
        // frames
        Array<StaticTiledMapTile> frameTiles = new Array<StaticTiledMapTile>(2);
        // get frame tiles
        for(TiledMapTile tile : map.getTileSets().getTileSet("tiles"))
        {
            if(tile.getProperties().containsKey("animation") &&
                    tile.getProperties().get("animation", String.class).equals("flower"))
                frameTiles.add((StaticTiledMapTile) tile);
        }
        // create the animated tile
        AnimatedTiledMapTile animatedTile = new AnimatedTiledMapTile(1 / 3.f, frameTiles);

        TiledMapTileLayer layer = (TiledMapTileLayer) map.getLayers().get("background");
        for(int x = 0; x < layer.getWidth(); ++x)
        {
            for(int y = 0; y < layer.getHeight(); ++y)
            {
                TiledMapTileLayer.Cell cell = layer.getCell(x, y);

                if(cell.getTile().getProperties().containsKey("animation") &&
                        cell.getTile().getProperties().get("animation", String.class).equals("flower"))
                {
                    cell.setTile(animatedTile);
                }
            }
        } */
        //////////////////////////////////////////////////////////////////////////////

        backgroundLayers = new int[] {0, 1};
        foregroundLayers = new int[] { 2, 3 };

        tileMap = new TileMap("maps/map.tmx");
        tileMap.setCamera(camera);
        // Get renderer sprite batch
        spriteBatch = tileMap.getSpriteBatch();

        Texture playerTexture = new Texture("img/playerFrames/still1.png");
        playerTexture.setFilter(Texture.TextureFilter.Nearest, Texture.TextureFilter.Nearest);

        player = new Character(playerTexture);
        player.setCollisionLayer(new CollisionLayer(tileMap.getTileLayer(1)));
        player.setDimensions(32, 32);
        // Do programatically, optimize
        tileMap.setLayerOpacity(0, 1);

        resetPlayer();
        //player.setSize(3 * player.getWidth(), 3 * player.getHeight());
    }

    private void resetMap()
    {
        tileMap.reload("maps/map.tmx");

        player.setCollisionLayer(new CollisionLayer(tileMap.getTileLayer(1)));
    }

    private void resetPlayer()
    {
        // Get spawn position rectangle
        RectangleMapObject spawnPos = (RectangleMapObject) tileMap.getLayer("objects").getObjects().get("SpawnPosition");
        player.setPosition(spawnPos.getRectangle().getX(), spawnPos.getRectangle().getY());

        camera.zoom = 1.f;

        player.setVelocity(100, 0);
    }

    @Override
    public void hide()
    {
        tileMap.dispose();
    }

    @Override
    public void pause()
    {
    }

    @Override
    public void resume()
    {
    }

    @Override
    public void dispose()
    {
    }
}
