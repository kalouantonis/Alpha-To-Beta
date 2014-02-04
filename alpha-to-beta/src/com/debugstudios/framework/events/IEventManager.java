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

package com.debugstudios.framework.events;

import ashley.signals.Listener;

import java.util.UUID;

/**
 * Created by slacker on 2/4/14.
 */
public abstract class IEventManager
{
    int INFINITE = 0xffffffff;

    public IEventManager(String name)
    {

    }

    public abstract void AddListener(Listener<IEventData> eventListener, UUID eventType);

    public abstract void RemoveListener(Listener<IEventData> eventListener, UUID eventType);

    public abstract void TriggerEvent(IEventData event);

    public abstract void QueueEvent(IEventData event);

    public abstract void AbortEvent(long eventType, boolean allOfType);

    public abstract void Update(float maxMillis);

    public void Update()
    {
        Update(INFINITE);
    }
}
