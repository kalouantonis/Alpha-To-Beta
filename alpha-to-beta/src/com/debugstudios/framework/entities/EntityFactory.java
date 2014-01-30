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

package com.debugstudios.framework.entities;

import java.util.TreeMap;

/**
 * Created by Antonis Kalou on 1/28/14.
 */
// TODO: Factory does all entity parsing. Create automagic ID's.
public abstract class EntityFactory<T>
{
    protected TreeMap<String, T> entityTemplateMap;

    public EntityFactory()
    {
        entityTemplateMap = new TreeMap<String, T>();
    }

    public abstract T create(String tag, float x, float y);

    public void addEntityTemplate(String tag, T template)
    {
        entityTemplateMap.put(tag, template);
    }

    public void clearEntityTemplates()
    {
        entityTemplateMap.clear();
    }

    public boolean contains(String tag)
    {
        return entityTemplateMap.containsKey(tag);
    }

    public boolean contains(T entity)
    {
        return entityTemplateMap.containsValue(entity);
    }
}
