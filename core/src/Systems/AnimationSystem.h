#ifndef _ANIMATION_SYSTEM_H_
#define _ANIMATION_SYSTEM_H_

#include <Systems/BaseRenderSystem.h>
#include <Systems/BaseRenderSystem.cpp>

#include <Components/BaseAnimation.h>

class AnimationSystem: public BaseRenderSystem<BaseAnimation>
{
public:
	AnimationSystem(SpriteBatch& spriteBatch);

private:
	virtual void updateRenderable(BaseAnimation* pRenderable) final;
};

#endif // !_ANIMATION_SYSTEM_H_

