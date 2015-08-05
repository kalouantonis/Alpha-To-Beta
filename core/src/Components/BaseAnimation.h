#ifndef _BASE_ANIMATION_H_
#define _BASE_ANIMATION_H_

#include <Components/IRenderable.h>

#include <Graphics/Animation.h>

#include <string>
#include <unordered_map>

class BaseAnimation: public IRenderable
{
public:
	BaseAnimation(int order = 0, float height = 0.f, float width = 0.f);
	virtual ~BaseAnimation();

	virtual const TextureRegion& getTextureRegion() const;

    static const char* g_name;
    virtual const char* getName() const final { return g_name; }

	virtual bool load(const tinyxml2::XMLElement* pElement);

	void setFrameTime(float frameTime) { m_stateTime += frameTime; }

	bool setAnimationGroup(const std::string& groupName);
	const std::string& getAnimationGroup() const { return m_currentGroup; }

protected:
	// Use unique pointers because this object is the sole owner of the animation
	// Also, can't use stack objects, as there is not default constructor
	typedef std::unordered_map<std::string, UAnimationPtr> AnimationGroupMap;
	AnimationGroupMap m_animationGroups;


private:
	float m_stateTime;

	std::string m_currentGroup;
	const Animation* m_currentAnimation;

	float m_width;
	float m_height;
};

#endif