/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2014] [Antonis Kalou (kalouantonis@gmail.com)]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.debugstudios.framework.systems;

import ashley.core.Engine;
import ashley.core.Entity;
import ashley.core.EntitySystem;
import ashley.core.Family;
import ashley.utils.IntMap;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.debugstudios.framework.components.CameraComponent;
import com.debugstudios.framework.components.Renderable;
import com.debugstudios.framework.components.Transform;
import com.debugstudios.framework.graphics.Camera;

import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Antonis Kalou on 1/29/14.
 */
public class RenderSystem extends EntitySystem
{
    // TODO: Use comparator to compare positional z co-ords
    IntMap<Entity> renderables;

    Family renderableFamily;

    SpriteBatch spriteBatch;

    public RenderSystem(Rectangle worldSize)
    {
        this(new SpriteBatch(), worldSize);
    }

    public RenderSystem(int priority, Rectangle worldSize)
    {
        this(priority, new SpriteBatch(),  worldSize);
    }

    /**
     * Set up the rendering system
     *
     * @param spriteBatch
     */
    public RenderSystem(SpriteBatch spriteBatch, Rectangle worldSize)
    {
        this(0, spriteBatch, worldSize);
    }

    public RenderSystem(int priority, SpriteBatch spriteBatch, Rectangle worldSize)
    {
        super(priority);

        renderables = new IntMap<Entity>();
        renderableFamily = Family.getFamilyFor(Transform.class, Renderable.class);

        this.spriteBatch = spriteBatch;
    }

    /**
     *
     * @param engine The Engine this system was added to
     */
    @Override
    public void addedToEngine(Engine engine)
    {
        super.addedToEngine(engine);

        // TODO: Check if super classes are counted in renderable
        renderables = engine.getEntitiesFor(renderableFamily);
    }

    @Override
    public void update(float deltaTime)
    {
        // Clear screen buffer
        Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);

        IntMap.Keys keys = renderables.keys();

        spriteBatch.begin();

        while(keys.hasNext)
        {
            Entity entity = renderables.get(keys.next());

            Transform transformComp = entity.getComponent(Transform.class);
            Renderable renderableComp = entity.getComponent(Renderable.class);

            Rectangle transform = transformComp.transform;
            Vector2 origin = transformComp.origin;
            Vector2 scale = transformComp.scale;

            spriteBatch.draw(
                    renderableComp.texture, transform.x, transform.y,
                    origin.x, origin.y,
                    transform.width, transform.height,
                    scale.x, scale.y,
                    transformComp.rotation,
                    0, 0, (int)transform.width, (int)transform.height,
                    renderableComp.flipX, renderableComp.flipY
            );
        }

        spriteBatch.end();
    }
}
