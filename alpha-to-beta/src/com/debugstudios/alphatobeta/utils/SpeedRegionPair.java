/*
 * Copyright (C) Debug Studios, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Antonis Kalou <kalouantonis@gmail.com>, 12 2013
 */

package com.debugstudios.alphatobeta.utils;

import com.badlogic.gdx.utils.Array;

/**
 * Created by Antonis Kalou on 20/12/13.
 */
public class SpeedRegionPair
{
    private float speed;
    private Array<String> regions;

    public SpeedRegionPair()
    {
        this.speed = 0.f;
        this.regions = new Array<String>();
    }

    public SpeedRegionPair(float speed, Array<String> regions)
    {
        this.speed = speed;
        this.regions = regions;
    }

    public void clear()
    {
        this.speed = 0.f;
        this.regions.clear();
    }

    public float getSpeed()
    {
        return speed;
    }

    public Array<String> getRegions()
    {
        return regions;
    }

    public void setSpeed(float speed)
    {
        this.speed = speed;
    }

    public void setRegions(Array<String> regions)
    {
        this.regions = regions;
    }

    public void addRegion(String region)
    {
        this.regions.add(region);
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        SpeedRegionPair that = (SpeedRegionPair) o;

        if (Float.compare(that.speed, speed) != 0) return false;
        if (regions != null ? !regions.equals(that.regions) : that.regions != null) return false;

        return true;
    }

    @Override
    public String toString()
    {
        return "SpeedRegionPair{" +
                "speed=" + speed +
                ", regions=" + regions +
                '}';
    }
}
