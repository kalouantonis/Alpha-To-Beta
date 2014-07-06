#include <Systems/AnimationSystem.h>

#include <Graphics/SpriteBatch.h>

AnimationSystem::AnimationSystem(SpriteBatch& spriteBatch)
	: BaseRenderSystem(spriteBatch)
{

}

void AnimationSystem::updateRenderable(BaseAnimation* pRenderable)
{
	pRenderable->setFrameTime(getDelta());
}