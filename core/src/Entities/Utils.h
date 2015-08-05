#ifndef UTILS_H_
#define UTILS_H_

#include <Artemis/Entity.h>

template <class T>
/**
 * @brief safeGetComponent Attempt to get component from entity. If it does
 * not exist or entity is null, a nullptr will be returned
 *
 * @param pEntity pEntity to get component from
 * @return requested component or nullptr if failed to grab it
 */
T* safeGetComponent(artemis::Entity* pEntity) 
{
    if(pEntity)
    {
        artemis::Component* pComp = pEntity->getComponent<T>();

        if(pComp)
            return static_cast<T*>(pComp);
    }

    return nullptr;
}

std::string getGroupName(artemis::Entity& e);

#endif // UTILS_H_
