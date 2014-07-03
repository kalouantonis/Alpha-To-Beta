#ifndef _BASE_ANIMATION_H_
#define _BASE_ANIMATION_H_

#include <Components/IRenderable.h>
#include <Graphics/Animation.h>

#include <unordered_map>

class BaseAnimation: public IRenderable
{
public:
	BaseAnimation();
	virtual ~BaseAnimation();

	virtual const TextureRegion& getTextureRegion() const;

	virtual bool load(const tinyxml2::XMLElement* pElement);

protected:
	//typedef std::unordered_map<std::string, Animation> AnimationGroupMap;
	//AnimationGroupMap m_animationGroups;
};

#endif