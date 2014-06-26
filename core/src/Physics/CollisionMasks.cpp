#include <Physics/CollisionMasks.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

void changeFixtureFilterMaskFlags(b2Body* pBody, CollisionMasks mask)
{
	for(b2Fixture* pFixture = pBody->GetFixtureList(); pFixture != NULL; pFixture = pFixture->GetNext())
	{
		// Get filter
		b2Filter filter = pFixture->GetFilterData();
		// Set to mask
		filter.maskBits = mask;

		pFixture->SetFilterData(filter);
	}
}