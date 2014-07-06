#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <Graphics/TextureRegion.h>

#include <vector>

class Animation 
{
public:
	typedef std::vector<TextureRegion> KeyFrames;

	enum PlayMode 
	{
		NORMAL,			// Run frame by frame in order once
		REVERSED,		// Run frame by frame in reversed order once
		LOOP,			// Loop frame by frame
		LOOP_REVERSED,	// Loop frame by frame in reversed order
		LOOP_RANDOM		// Loop in random order
	};

	Animation(float frameDuration, const KeyFrames& keyFrames);
	Animation(float frameDuration, const KeyFrames& keyFrames, PlayMode playMode);
	~Animation();
	
	//TextureRegion& getKeyFrame(float stateTime);
	const TextureRegion& getKeyFrame(float stateTime) const;
	const std::vector<TextureRegion>& getKeyFrames() const { return m_keyFrames; }

	PlayMode getPlayMode() const { return m_kPlayMode; }
	void setPlayMode(PlayMode kPlayMode) { m_kPlayMode = kPlayMode; }

	float getFrameDuration() const { return m_frameDuration; }
	void setFrameDuration(float frameDuration) { m_frameDuration = frameDuration; }

	float getAnimationDuration() const { return m_animationDuration; }
	bool isAnimationFinished(float stateTime) const;

private:
	int getKeyFrameIndex(float stateTime) const;

	KeyFrames m_keyFrames;
	PlayMode m_kPlayMode;

	float m_frameDuration;
	float m_animationDuration;

};

typedef std::unique_ptr<Animation> UAnimationPtr;
typedef std::shared_ptr<Animation> AnimationPtr;

#endif