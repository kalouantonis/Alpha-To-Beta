/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.framework.utils;

/**
 * Created by Antonis Kalou on 23/12/13.
 */
public class Cleanup
{
    private static final String TAG = Cleanup.class.getSimpleName();

    /**
     * Request the GC run. This is only a request however,
     * the GC is allowed to ignore it.
     *
     */
    public static void requestGC()
    {
        // Call GC to clean up
        Debug.dumpHeap(TAG);

        System.gc();

        Debug.dumpHeap(TAG);
    }
}
