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
public class Cleanup
{
    public static void requestGC(String tag)
    {
        // Call GC to clean up
        Gdx.app.debug(tag, "Calling GC...");
        Debug.dumpHeap(tag);

        System.gc();


        Gdx.app.debug(tag, "GC Called.");
        Debug.dumpHeap(tag);
    }
}
