#ifndef _LOOSE_PTR_H
#define _LOOSE_PTR_H

#include <memory>


template <class T>
/**
 * @brief Create object that will not be deleted automagically
 * @param p Pointer to create loose_ptr for
 * @return New shared_ptr with empty deleter
 */
inline std::shared_ptr<T> loose_ptr(T* p)
{
    // Void deleter lambda
    return std::shared_ptr<T>(p, [](T* p) {});
}

#endif // _LOOSE_PTR_H
