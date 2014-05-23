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

template <typename T>
inline bool isZero(const sf::Vector2<T>& vec)
{
    return ((vec.x == 0) && (vec.y == 0));
}

#endif // VECTOR_H
	
