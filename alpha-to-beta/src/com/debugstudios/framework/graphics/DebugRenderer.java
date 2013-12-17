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
    /** Renderer used for bounding boxes, etc. */
    private ShapeRenderer shapeRenderer;
    /** Font renderer for debug information */
    private BitmapFont debugFont = null;
    /** Camera, used for rendering fonts */
    private Camera camera;

    /**
     * Create new debug renderer, load internal renderers
     *
     * @param camera Camera instance
     */
    public DebugRenderer(Camera camera)
    {
        shapeRenderer = new ShapeRenderer();

        this.camera = camera;
    }

    // TODO: Allow loading using AssetManager

    /**
     * Load bitmap font
     *
     * @param internalFont Internal font file, contains font information
     * @param internalImage Bitmap image of font
     */
    public void loadFont(String internalFont, String internalImage)
    {
        debugFont = new BitmapFont(Gdx.files.internal(internalFont),
                Gdx.files.internal(internalImage), false);
    }

    /**
     * Begin renderer, call before drawing entities
     */
    public void begin()
    {
        shapeRenderer.setProjectionMatrix(camera.combined);

        shapeRenderer.begin(ShapeRenderer.ShapeType.Line);
    }

    /**
     * Draw entity debug info --> bounding box
     *
     * @param entity Entity to render info for
     * @param color Color of bounding rect
     */
    public void draw(Entity entity, Color color)
    {
        shapeRenderer.rect(entity.position.x, entity.position.y, entity.width, entity.height,
                color, color, color, color);
    }

    /**
     * Draw dynamic entity --> bounding box && velocity vector
     *
     * @param entity Dynamic entity to render info for
     * @param rectColor Color of bounding rect
     * @param lineColor Color of velocity lines
     */
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

    /**
     * Delegate method, get the height of the preloaded font
     *
     * @return Height of font characters
     */
    public float getFontHeight()
    {
        return debugFont.getLineHeight();
    }

    /**
     * End renderer, call after drawing entities
     */
    public void end()
    {
        shapeRenderer.end();
    }

    /**
     * Dispose of internal files
     */
    public void dispose()
    {
        shapeRenderer.dispose();
        debugFont.dispose();
    }
}
