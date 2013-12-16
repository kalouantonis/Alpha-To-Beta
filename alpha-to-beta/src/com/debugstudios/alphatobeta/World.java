package com.debugstudios.alphatobeta;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.maps.objects.RectangleMapObject;
import com.debugstudios.alphatobeta.framework.tilemap.CollisionLayer;
import com.debugstudios.alphatobeta.framework.tilemap.TileMap;
import com.debugstudios.alphatobeta.models.Player;

/**
 * Created by slacker on 12/9/13.
 */
public class World
{
    public TileMap tileMap;
    public CollisionLayer collisionLayer;

    public Player player = null;

    boolean jumpKeyPressed = false;

    public World(TileMap tileMap)
    {
        this.tileMap = tileMap;

        collisionLayer = new CollisionLayer(tileMap.getTileLayer(1));

        reloadScene();
    }

    public void handleInput()
    {
        if(Gdx.input.isKeyPressed(Input.Keys.R))
            reloadScene();
    }

    private void reloadScene()
    {
        tileMap.reload("maps/map.tmx");

        RectangleMapObject spawnPos = (RectangleMapObject) tileMap.getLayer("objects").getObjects().get("SpawnPosition");
        if(player == null)
        {
            TextureRegion playerTexture = Assets.runRightAnimation.getKeyFrame(0);

            player = new Player(spawnPos.getRectangle().x, spawnPos.getRectangle().y,
                    playerTexture.getRegionWidth(), playerTexture.getRegionHeight());
            player.setCollisionLayer(collisionLayer);

            Gdx.input.setInputProcessor(new PlayerInputHandler(player));
        }
        else
        {
            player.position.x = spawnPos.getRectangle().x;
            player.position.y = spawnPos.getRectangle().y;
        }
    }

    public void update(float deltaTime)
    {
        updateCharacters(deltaTime);
        checkCharacterCollisions();
    }

    private void checkCharacterCollisions()
    {
    }

    private void updateCharacters(float deltaTime)
    {
        player.update(deltaTime);
    }
}
