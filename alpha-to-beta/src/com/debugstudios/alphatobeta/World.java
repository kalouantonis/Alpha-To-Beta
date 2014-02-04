/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta;

import ashley.core.Engine;
import ashley.core.PooledEngine;
import com.badlogic.gdx.Files;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Rectangle;
import com.debugstudios.alphatobeta.players.Player;
import com.debugstudios.alphatobeta.systems.PlayerInputSystem;
import com.debugstudios.framework.entities.ParsedEntity;
import com.debugstudios.framework.graphics.Camera;
import com.debugstudios.framework.managers.TextureManager;
import com.debugstudios.framework.systems.CameraSystem;
import com.debugstudios.framework.systems.MovementSystem;
import com.debugstudios.framework.systems.RenderSystem;
import com.debugstudios.framework.tilemap.CollisionLayer;

import java.util.ArrayList;

/**
 * Created by Antonis Kalou on 12/9/13.
 */
public class World
{
    private static final String TAG = World.class.getSimpleName();

    public static final float WORLD_WIDTH = 480;
    public static final float WORLD_HEIGHT = 360;

    private final int NUM_PLAYERS = 5;
//    private final TileMap tileMap;

    //    public TileMap tileMap;
    private Camera camera;

    private PooledEngine engine;

    //public Player player = null;
    // NOTE: If using threads, use Vector --> Is the very bestest best when thread run...
//    public ArrayList<Player> players;
    private SpriteBatch spriteBatch;

//    public QuadTree obstacleGrid;
//    List<Entity> possibleColliders;

    public World()
    {
        //this.camera = new Camera(WORLD_WIDTH, WORLD_HEIGHT);

        //Gdx.app.debug(TAG, "Created camera. Viewport --> width: " + WORLD_WIDTH + "\theight: " + WORLD_HEIGHT);

//        this.tileMap = new TileMap();
//        this.tileMap.setCamera(camera);

//        players = new ArrayList<Player>(NUM_PLAYERS);

//        obstacleGrid = new QuadTree(0, new Rectangle(0, 0, WORLD_WIDTH * 2, WORLD_HEIGHT * 2));
//        possibleColliders = new ArrayList<Entity>();
        spriteBatch = new SpriteBatch();

        engine = new PooledEngine();
        engine.addSystem(new RenderSystem(5, spriteBatch, new Rectangle(0, 0, 1000, 500)));
        //engine.addSystem(new MovementSystem());
        engine.addSystem(new CameraSystem(8, spriteBatch));
        engine.addSystem(new PlayerInputSystem(9));
        engine.addSystem(new MovementSystem(10, new CollisionLayer(1000, 500, 16, 16)));

        // TODO: Thread this, show loading screen
        reloadScene();
    }

    public void pollInput()
    {
        if(Gdx.input.isKeyPressed(Input.Keys.R))
            reloadScene();

//        if(Gdx.input.isKeyPressed(Input.Keys.PLUS))
//            player.MOVE_VELOCITY += 10;
//        else if(Gdx.input.isKeyPressed(Input.Keys.MINUS))
//            player.MOVE_VELOCITY -= 10;
        else if(Gdx.input.isKeyPressed(Input.Keys.ESCAPE))
            Gdx.app.exit();
        // Only for debugging
        else if(Gdx.input.isKeyPressed(Input.Keys.CONTROL_LEFT))
            camera.addZoom(0.1f);
        else if(Gdx.input.isKeyPressed(Input.Keys.SHIFT_LEFT))
            camera.addZoom(-0.1f);
    }

    private void reloadScene()
    {

        Gdx.app.debug(TAG, "Reloading scene...");

//        tileMap.reload();
//        Assets.mapLoader.load("objects/maps/map.xml", tileMap);
//        tileMap.getCamera().zoom = 1.f;
//        Gdx.app.debug(TAG, "Reloaded tile map.");

        // Reset collision layer
//        Gdx.app.debug(TAG, "Reloaded collision layer.");


//        RectangleMapObject spawnPos = (RectangleMapObject) tileMap.getLayer("objects").getObjects().get("SpawnPosition");
//        if(player == null)
//        {
//            try
//            {
//                player = new HumanPlayer(spawnPos.getRectangle().x, spawnPos.getRectangle().y);
//            }
//            catch (NullPointerException e)
//            {
//                throw new RuntimeException("No spawn point implemented! Add a SpawnPoint object to the map" +
//                                            tileMap.getFileName() != null ? ": " + tileMap.getFileName() : "");
//            }
            // Add to array, keep reference for direct access
        Gdx.app.debug(TAG, "Clearing previous textures...");
        TextureManager.getInstance().clear();

        Gdx.app.debug(TAG, "Clearing previous entities...");
        engine.removeAllEntities();

        ParsedEntity camera = new ParsedEntity();
        camera.load("objects/Camera.xml", Files.FileType.Internal);
        engine.addEntity(camera);

        ParsedEntity player = new ParsedEntity();
        player.load("objects/players/EntityPlayer.xml", Files.FileType.Internal);
        engine.addEntity(player);

            //players.add(player);

//            camera.setTarget(player);
//        }
//        else
//        {
//            player.position.x = spawnPos.getRectangle().x;
//            player.position.y = spawnPos.getRectangle().y;
//            player.velocity.set(0, 0);
//        }

//        player.setCollisionLayer(new CollisionLayer(tileMap.getTileLayer(1)));

        // Load rest of attributes from loaders
//        Assets.playerLoader.load("objects/players/HumanPlayer.xml", player, Assets.humanPlayerSheet);

        Gdx.app.debug(TAG, "Player loaded.");

        // Clear previous quad tree
//        obstacleGrid.clear();

/*
        // Load obstacles
        ObstacleFactory factory = new ObstacleFactory();
        Assets.obstacleLoader.loadDirectory("objects/obstacles", factory, false);

        // TODO: load layer index from conf file
        // TODO: parse blocks of map, request new data every 1000 tiles or so
        TiledMapTileLayer objectLayer = tileMap.getTileLayer(2);
        int layerWidth = objectLayer.getWidth();
        int layerHeight = objectLayer.getHeight();
        float tileWidth = objectLayer.getTileWidth();
        float tileHeight = objectLayer.getTileHeight();

        Iterator<String> keyIter;
        String id;

        for(int x = 0; x < layerWidth; ++x)
        {
            for(int y = 0; y < layerHeight; ++y)
            {
                TiledMapTileLayer.Cell cell = objectLayer.getCell(x, y);

                if(cell != null)
                {
                    // Find property of cell
                    keyIter = cell.getTile().getProperties().getKeys();
                    while(keyIter.hasNext())
                    {
                        id = keyIter.next();

                        // Check if contained within factory
                        if(factory.contains(id))
                        {
                            // Insert in to obstacle grid
                            obstacleGrid.insert(
                                    factory.create(
                                            // ID from object
                                            id,
                                            // X World coords
                                            x * tileWidth,
                                            // Y World coords. Y is inverted
                                            y * tileHeight
                                    )
                            );

                            break;
                        }
                    }
                }
            }
        }
*/

        Gdx.app.debug(TAG, "Scene reloaded successfully!");
    }

    public void update(float deltaTime)
    {
//        possibleColliders.clear();

        engine.update(deltaTime);
        /*obstacleGrid.retrieve(possibleColliders, player);

        if(!possibleColliders.isEmpty())
        {
            for(Entity collider : possibleColliders)
            {
                if(OverlapTester.overlapEntities(player, collider))
                {
                    //Gdx.app.debug(TAG, "Collision detected");
                    float slowdown = ((Obstacle)collider).slowdown;

                    // FIXME: Jesus man, fix this
                    player.velocity.x -= player.velocity.x < 0 ? -slowdown : slowdown;
                }
            }
        }

        updateCharacters(deltaTime);

        if(player.position.y < 0)
            reloadScene();*/
    }

    private void updateCharacters(float deltaTime)
    {
//        for(Player character : players)
//        {
//            character.update(deltaTime);
//        }
    }

    public Camera getCamera()
    {
        return camera;
    }

    public void dispose()
    {
//        tileMap.dispose();
//        obstacleGrid.clear();
        engine.removeAllEntities();
        TextureManager.getInstance().clear();
    }
}
