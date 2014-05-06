#ifndef VECTOR_H
#define VECTOR_H
	
#include <Box2D/Common/b2Math.h>
#include <SFML/System/Vector2.hpp>

inline b2Vec2 toB2Vec(const sf::Vector2f& vector)
{
	return b2Vec2(vector.x, vector.y);
}

inline sf::Vector2f toSFVec(const b2Vec2& vector)
{
	return sf::Vector2f(vector.x, vector.y);
}

#endif // VECTOR_H
	