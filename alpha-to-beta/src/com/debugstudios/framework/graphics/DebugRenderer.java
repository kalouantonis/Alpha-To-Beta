package com.debugstudios.framework.graphics;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.debugstudios.framework.gameobjects.DynamicEntity;
import com.debugstudios.framework.gameobjects.Entity;

/**
 * Created by slacker on 14/12/13.
 */
public class DebugRenderer
{
    private ShapeRenderer shapeRenderer;
    private BitmapFont debugFont = null;
    private Camera camera;

    public DebugRenderer(Camera camera)
    {
        shapeRenderer = new ShapeRenderer();

        this.camera = camera;
    }

    // TODO: Allow loading using AssetManager
    public void loadFont(String internalFont, String internalImage)
    {
        debugFont = new BitmapFont(Gdx.files.internal(internalFont),
                Gdx.files.internal(internalImage), false);
    }

    public void begin()
    {
        shapeRenderer.setProjectionMatrix(camera.combined);

        shapeRenderer.begin(ShapeRenderer.ShapeType.Line);
    }

    public void draw(Entity entity, Color color)
    {
        shapeRenderer.rect(entity.position.x, entity.position.y, entity.width, entity.height,
                color, color, color, color);
    }

    public void draw(DynamicEntity entity, Color rectColor, Color lineColor)
    {
        shapeRenderer.rect(entity.position.x, entity.position.y, entity.width, entity.height,
                rectColor, rectColor, rectColor, rectColor);

        float halfWidth = entity.position.x + (entity.width / 2);
        float halfHeight = entity.position.y + (entity.height / 2);

        // Draw X Vel
        shapeRenderer.line(halfWidth, halfHeight,
                halfWidth + entity.velocity.x, halfHeight, lineColor, lineColor);
        // Draw Y vel
        shapeRenderer.line(halfWidth, halfHeight,
                halfWidth, halfHeight + entity.velocity.y, lineColor, lineColor);
    }

    /**
     * Abstract from font drawing, provide absolute screen positioning
     */
    public void drawFont(SpriteBatch spriteBatch, String text, float x, float y)
    {
        if(debugFont != null)
        {
            // Scale according to camera zoom for consistent size
            debugFont.setScale(camera.zoom);

            debugFont.draw(spriteBatch, text,
                    (camera.position.x - (camera.viewportWidth / 2) * camera.zoom) + x,
                    (camera.position.y + (camera.viewportHeight / 2) * camera.zoom) - y);
        }
    }

    public float getFontHeight()
    {
        return debugFont.getLineHeight();
    }

    public void end()
    {
        shapeRenderer.end();
    }

    public void dispose()
    {
        shapeRenderer.dispose();
        debugFont.dispose();
    }
}
