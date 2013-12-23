/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.framework.utils;

import com.badlogic.gdx.Gdx;

/**
 * Created by Antonis Kalou on 23/12/13.
 */
public class Debug
{
    public static void dumpHeap(String tag)
    {
        Gdx.app.debug(tag, "\tJava Heap: " + Gdx.app.getJavaHeap() + '\n' +
                "\t\tNative Heap: " + Gdx.app.getNativeHeap());
    }
}
