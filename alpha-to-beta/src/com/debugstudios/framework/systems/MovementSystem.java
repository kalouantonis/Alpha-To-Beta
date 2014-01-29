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

import ashley.core.Entity;
import ashley.core.Family;
import ashley.systems.IteratingSystem;
import com.debugstudios.framework.components.Movement;
import com.debugstudios.framework.components.Transform;
import com.debugstudios.framework.tilemap.CollisionLayer;

/**
 * Created by Antonis Kalou on 1/29/14.
 */
public class MovementSystem extends IteratingSystem
{
    CollisionLayer collisionLayer;

    public MovementSystem(CollisionLayer collisionLayer)
    {
        super(Family.getFamilyFor(Transform.class, Movement.class));

        this.collisionLayer = collisionLayer;
    }

    @Override
    public void processEntity(Entity entity, float deltaTime)
    {
        Transform transform = entity.getComponent(Transform.class);
        Movement movement = entity.getComponent(Movement.class);


    }
}
