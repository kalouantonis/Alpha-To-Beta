#ifndef _COLLISION_MASKS_H_
#define _COLLISION_MASKS_H_

//FWD Defs////////////////////////////////////////////////////////////////
class b2Body;
//////////////////////////////////////////////////////////////////////////

enum CollisionMasks
{
	NO_COLLIDE = 0x0000,
	COLLIDE = 0x0001
};

void changeFixtureFilterMaskFlags(b2Body* pBody, CollisionMasks mask);

#endif