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

package com.debugstudios.framework.managers;

import ashley.utils.ObjectMap;
import com.badlogic.gdx.Gdx;

/**
 * Created by slacker on 2/4/14.
 *
 * Used for items that need disposing, so that no referenced items are deleted
 */
public abstract class ObjectReferenceManager<T>
{
    private static final String TAG = ObjectReferenceManager.class.getSimpleName();

    private ObjectMap<String, IntObjectPair<T>> objectMap;

    public ObjectReferenceManager()
    {
        objectMap = new ObjectMap<String, IntObjectPair<T>>();
    }

    public T load(String filename)
    {
        IntObjectPair<T> objectPair = objectMap.get(filename, null);

        if(objectPair == null)
        {
            objectPair = new IntObjectPair<T>(0, createObject(filename));
            objectMap.put(filename, objectPair);
        }

        // Increment reference count
        ++objectPair.first;

        return objectPair.second;
    }


    protected abstract T createObject(String filename);

    public boolean contains(String filename)
    {
        return objectMap.containsKey(filename);
    }

    public T get(String filename)
    {
        return objectMap.get(filename).second;
    }

    public void remove(String filename)
    {
        IntObjectPair<T> objectPair = objectMap.get(filename);

        // Decrement reference count
        --objectPair.first;

        // Dispose if no longer referenced
        if(objectPair.first <= 0)
        {
            Gdx.app.debug(TAG, "Reference count reached zero. Disposing: " + filename);
            dispose(objectPair.second);
            objectMap.remove(filename);
        }
    }

    /**
     * Dispose of object that has lost all references
     */
    protected abstract void dispose(T object);

    public void clear()
    {
        // Dispose objects before clearing
        for(IntObjectPair<T> objectPair : objectMap.values())
        {
            dispose(objectPair.second);
        }

        objectMap.clear();
    }


    private class IntObjectPair<T>
    {
        private int first;
        private T second;

        public IntObjectPair()
        {
            first = 0;
            second = null;
        }

        public IntObjectPair(int first, T second)
        {
            this.first = first;
            this.second = second;
        }

        public void clear()
        {
            this.first = 0;
            this.second = null;
        }

        public int getFirst()
        {
            return first;
        }

        public void setFirst(int first)
        {
            this.first = first;
        }

        public T getSecond()
        {
            return second;
        }

        public void setSecond(T second)
        {
            this.second = second;
        }

        @Override
        public boolean equals(Object o)
        {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            IntObjectPair that = (IntObjectPair) o;

            if (first != that.first) return false;
            if (second != null ? !second.equals(that.second) : that.second != null) return false;

            return true;
        }

        @Override
        public int hashCode()
        {
            int result = first;
            result = 31 * result + (second != null ? second.hashCode() : 0);
            return result;
        }
    }
}
