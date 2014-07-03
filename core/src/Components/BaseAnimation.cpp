#include <Components/BaseAnimation.h>

BaseAnimation::BaseAnimation()
	: IRenderable(0)
{

}

BaseAnimation::~BaseAnimation()
{

}

const TextureRegion& BaseAnimation::getTextureRegion() const
{
	return TextureRegion();
}

bool BaseAnimation::load(const tinyxml2::XMLElement* pElement)
{
	return false;
}