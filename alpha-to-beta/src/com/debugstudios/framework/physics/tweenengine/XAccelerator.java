/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2013] [Antonis Kalou (kalouantonis@gmail.com)]
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

package com.debugstudios.framework.physics.tweenengine;

import com.debugstudios.framework.gameobjects.DynamicEntity;

/**
 * Created by Antonis Kalou on 12/30/13.
 */
public class XAccelerator implements Tween
    {
        DynamicEntity entity;

        float time;
        float xAccel;

        public XAccelerator(DynamicEntity entity, float finalXVel, float time)
        {
            this.entity = entity;
            this.time = time;

            // v = u + at
            // --> a = (v-u)/t
            xAccel = (finalXVel - entity.velocity.x) / time;

            entity.accel.x = xAccel;
        }

        public void update(float deltaTime)
        {
            if(time <= 0)
            {
                entity.accel.x = 0;
                return;
            }

            time -= deltaTime;
        }

        public boolean isFinished()
        {
            return time <= 0;
        }
    }

