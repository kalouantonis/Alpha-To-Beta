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

import com.badlogic.gdx.math.Vector2;
import com.debugstudios.framework.gameobjects.DynamicEntity;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by Antonis Kalou on 12/29/13.
 */
public class TweenEngine
{
    private List<Tween> tweens;

    public TweenEngine()
    {
        tweens = new ArrayList<Tween>();
    }

    public void addTween(Tween tween)
    {
        tweens.add(tween);
    }

    public void removeTween(Tween tween)
    {
        tweens.remove(tween);
    }

    public void removeTween(int index)
    {
        tweens.remove(index);
    }

    public void update(float deltaTime)
    {
        Iterator<Tween> iterator = tweens.iterator();

        while(iterator.hasNext())
        {
            Tween tween = iterator.next();
            tween.update(deltaTime);

            if(tween.isFinished())
                iterator.remove();
        }
    }


}
