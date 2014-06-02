#ifndef VECTOR_H
#define VECTOR_H
	
#include <Box2D/Common/b2Math.h>
#include <SFML/System/Vector2.hpp>

/**
 * @brief Convert SFML vector to Box2D vector

 * @param vector SFML vector to convert
 * @return Converted box2d vector
 */
inline b2Vec2 toB2Vec(const sf::Vector2f& vector)
{
	return b2Vec2(vector.x, vector.y);
}

/**
 * @brief Convert box2d vector to SFML vector
 * 
 * @param vector box2d vector to convert
 * @return Converted SFML vector
 */
inline sf::Vector2f toSFVec(const b2Vec2& vector)
{
	return sf::Vector2f(vector.x, vector.y);
}

template <typename T>
/**
 * @brief Check if SFML vector is zero
 * 
 * @param vec vector to check
 * @return true if zero
 */
inline bool isZero(const sf::Vector2<T>& vec)
{
    return ((vec.x == 0) && (vec.y == 0));
}

#endif // VECTOR_H
	
