#ifndef PHYSICS_H
#define PHYSICS_H

#include <Components/ParsedComponent.h>

#include <SFML/Graphics/Rect.hpp>

class b2Body;

class Physics: public ParsedComponent
{
	// Allow physics system to access hidden properties
	friend class PhysicsSystem;

public:
	Physics();
	explicit Physics(float width, float height);
	virtual ~Physics();

	// static const char* g_name;
	// virtual const char* getName() const override { return g_name; }

	const sf::Vector2f& getDimensions()
	{
		return m_dimensions;
	}

	/**
	 * @brief Set the object dimensions
	 * @details Must be re-initialized to commit changes to physics body
	 */
	void setDimensions(float width, float height);

	virtual bool load(const tinyxml2::XMLElement* pElement) override;
	/**
	 * @brief Initialize the physics body
	 * 
	 * @param x x position to initialize at
	 * @param y y position to initialize at
	 * @param rotation the rotation of the object, defaults to 0
	 */
	virtual void initialize(float x, float y, float rotation = 0.f) = 0;
	bool isInitialized() { return m_bInitialized; }

	sf::Vector2f getPosition();
	sf::Vector2f getOrigin();
	float getRotation();
	

	b2Body* body;

protected:
	sf::Vector2f m_dimensions;
	float m_halfWidth, m_halfHeight;
	bool m_bInitialized;
};

typedef std::shared_ptr<Physics> PhysicsPtr;

#endif // PHYSICS_H
