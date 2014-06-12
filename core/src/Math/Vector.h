#ifndef VECTOR_H
#define VECTOR_H
	
#include <Box2D/Common/b2Math.h>
#include <SFML/System/Vector2.hpp>

// FromVec is usually deduced. Set ToVec first because that is
// usually undeducable
/**
 * @brief Convert any 2D vector type to any other 2D vector type
 *
 * @param vector Vector to convert from
 * @tparam ToVec The vector type to convert to
 * @tparam FromVec The vector type to convert from. This is usually deduced by the compiler
 * @return the newly converted vector
 */
template <class ToVec, class FromVec>
inline ToVec toVec2(const FromVec& vector)
{
    return ToVec(vector.x, vector.y);
}

/**
 * @brief Check if SFML vector is zero
 * 
 * @param vec vector to check
 * @tparam T The type of the vector. Usually deduced by compiler
 * @return true if zero
 */
template <typename T>
inline bool isZero(const T& vec)
{
    return ((vec.x == 0) && (vec.y == 0));
}

#endif // VECTOR_H
	
