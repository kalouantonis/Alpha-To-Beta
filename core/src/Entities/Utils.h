#ifndef UTILS_H_
#define UTILS_H_

#include <Artemis/Entity.h>

template <class T>
/**
 * @brief safeGetComponent Attempt to get component from entity. If it does
 * not exist or entity is null, a nullptr will be returned
 *
 * @param entity Entity to get component from
 * @return requested component or nullptr if failed to grab it
 */
T* safeGetComponent(artemis::Entity* entity)
{
    if(entity)
    {
        artemis::Component* pComp = entity->getComponent<T>();

        if(pComp)
            return static_cast<T*>(pComp);
    }

    return nullptr;
}

#endif // UTILS_H_
