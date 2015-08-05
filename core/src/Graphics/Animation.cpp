#include <Graphics/Animation.h>
#include <Utils/Logger.h>

#include <glm/glm.hpp>

Animation::Animation(float frameDuration, const KeyFrames& keyFrames)
	: m_keyFrames(keyFrames)
	, m_kPlayMode(NORMAL)
	, m_frameDuration(frameDuration)
{
	// Dis-allow empty keyFrames
	CORE_ASSERT(!keyFrames.empty());
	// Get complete animation time through the number of regions and time for each frame
	m_animationDuration = keyFrames.size() * m_frameDuration;	
}

Animation::Animation(float frameDuration, const KeyFrames& keyFrames, PlayMode playMode)
	: m_keyFrames(keyFrames)
	, m_kPlayMode(playMode)
	, m_frameDuration(frameDuration)
{
	CORE_ASSERT(!keyFrames.empty());
	m_animationDuration = keyFrames.size() * m_frameDuration;
}

Animation::~Animation()
{
	m_keyFrames.clear();
}

//TextureRegion& Animation::getKeyFrame(float stateTime)
//{
//	return m_textureRegions[getKeyFrameIndex(stateTime)];
//}

const TextureRegion& Animation::getKeyFrame(float stateTime) const 
{
	return m_keyFrames[getKeyFrameIndex(stateTime)];
}

int Animation::getKeyFrameIndex(float stateTime) const
{
	CORE_ASSERT(stateTime >= 0.f);

	int numKeyFrames = m_keyFrames.size();

	if(numKeyFrames == 1) 
		return 0;

	// Get the current frame number
	int frameNumber = (unsigned int)(stateTime / m_frameDuration);

	switch(m_kPlayMode)
	{
	case NORMAL:
		// If all frames are played, only use last frame
		frameNumber = glm::min(numKeyFrames - 1, frameNumber);
		break;
	case LOOP:
		frameNumber %= numKeyFrames;
		break;
	case LOOP_RANDOM:
		frameNumber = rand() % numKeyFrames;
		break;
	case REVERSED:
		frameNumber = glm::max(numKeyFrames - frameNumber - 1, 0);
		break;
	case LOOP_REVERSED:
		frameNumber %= numKeyFrames;
		frameNumber = numKeyFrames - frameNumber - 1;
		break;
	};

	return frameNumber;
}

bool Animation::isAnimationFinished(float stateTime) const
{
	CORE_ASSERT(stateTime >= 0.f);
	unsigned int frameNumber = (unsigned int)(stateTime / m_frameDuration);
	return m_keyFrames.size() - 1 < frameNumber;
}