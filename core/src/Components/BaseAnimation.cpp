#include <Components/BaseAnimation.h>

#include <Resources/ResourceDef.h>

#include <Utils/String.h>
#include <Utils/Logger.h>

#include <tinyxml2.h>
#include "Physics/PhysicsLocator.h"

const char* BaseAnimation::g_name = "BaseAnimation";

BaseAnimation::BaseAnimation(int order, float height, float width)
	: IRenderable(order, width, height)
	, m_stateTime(0.f)
	, m_currentAnimation(nullptr)
{

}

BaseAnimation::~BaseAnimation()
{

}

const TextureRegion& BaseAnimation::getTextureRegion() const
{
	CORE_ASSERT(m_currentAnimation != nullptr);
	return m_currentAnimation->getKeyFrame(m_stateTime);
}

bool BaseAnimation::load(const tinyxml2::XMLElement* pElement)
{
	// Get draw order
	int order = getDrawOrder();
	pElement->QueryIntAttribute("order", &order);
	setDrawOrder(order);

	const tinyxml2::XMLElement* pChildElement = pElement->FirstChildElement("Texture");

	if(!pChildElement)
	{
		CORE_ERROR("No Texture element defined in BaseAnimation");
		return false;
	}

	// Get texture file
	std::string textureFile = make_string(pChildElement->GetText());

	if(textureFile.empty())
	{
		CORE_ERROR("No texture file defined in Texture element of BaseAnimation");
		return false;
	}

	trim(textureFile);

	// Attempt to receive texture from locator
	sf::TexturePtr pTexture = TextureLocator::getObject()->get(textureFile);

	if(!pTexture)
	{
		CORE_ERROR("Failed to get texture: " + textureFile);
		return false;
	}

	// Get dimensions
	pChildElement = pElement->FirstChildElement("Dimensions");

	if(pChildElement)
	{
		float width = getWidth();
		float height = getHeight();
		pChildElement->QueryFloatAttribute("width", &width);
		pChildElement->QueryFloatAttribute("height", &height);
		setWidth(width / PhysicsLocator::PixelsPerMeter.x);
		setHeight(height / PhysicsLocator::PixelsPerMeter.y);
	}

	// Iterate over groups
	for(pChildElement = pElement->FirstChildElement("Group"); pChildElement != NULL; 
		pChildElement = pChildElement->NextSiblingElement("Group"))
	{
		std::string groupName = make_string(pChildElement->Attribute("name"));

		if(groupName.empty())
		{
			CORE_WARNING("Ignoring empty group name");
			continue;
		}

		// Set default as zero
		float frameDuration = 0.f;

		// Get duration of every frame
		const tinyxml2::XMLElement* pFreqElement = pChildElement->FirstChildElement("Frequency");
		if(pFreqElement)
			pFreqElement->QueryFloatText(&frameDuration);

		std::vector<TextureRegion> regions;

		// Iterate over groups
		for(const tinyxml2::XMLElement* pRegionElement = pChildElement->FirstChildElement("Region"); pRegionElement != NULL;
			pRegionElement = pRegionElement->NextSiblingElement("Region"))
		{
			// Initialize all to zero by default
			float x = 0.f, y = 0.f; 
			float width = 0.f, height = 0.f;

			pRegionElement->QueryFloatAttribute("x", &x);
			pRegionElement->QueryFloatAttribute("y", &y);
			pRegionElement->QueryFloatAttribute("width", &width);
			pRegionElement->QueryFloatAttribute("height", &height);

			// Create texture
			regions.push_back(TextureRegion(pTexture, x, y, width, height));
		}

		// Create animation class and add to relevant group
		// TODO: Allow setting animation type
		m_animationGroups[groupName] = UAnimationPtr(new Animation(frameDuration, regions, Animation::LOOP));
	}

	m_currentAnimation = m_animationGroups.begin()->second.get();

	return true;
}

bool BaseAnimation::setAnimationGroup(const std::string& groupName)
{
	auto findIt = m_animationGroups.find(groupName);

	if(findIt != m_animationGroups.end())
	{
		m_currentGroup = groupName;
		m_currentAnimation = (*findIt).second.get();

		return true;
	}

	return false;
}