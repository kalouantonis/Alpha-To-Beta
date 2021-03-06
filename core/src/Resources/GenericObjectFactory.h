#ifndef GENERICOBJECTFACTORY_H
#define GENERICOBJECTFACTORY_H

#include <functional>
#include <unordered_map>

#include <Utils/Logger.h>

template <class BaseType, class SubType>
BaseType* GenericObjectCreator(void) { return new SubType; }

template <class Identifier, class BaseClass>
class GenericObjectFactory
{
public:
    ~GenericObjectFactory()
    {
        if(!m_creators.empty())
            m_creators.clear();
    }

    /**
     * @brief Registers a new object creator
     * @param id The identifier used
     * @return true if actually registered a new item, false if already exists
     */
    template <class SubClass>
    bool declare(const Identifier& id)
    {
        auto findIt = m_creators.find(id);
        if(findIt == m_creators.end()) // not found
        {
            // Store function pointer
            m_creators[id] = GenericObjectCreator<BaseClass, SubClass>;
            return true;
        }

        // Already registered
        return false;
    }

    /**
     * @brief Create new object from the predefined ID
     * @details Create a new object in the type of BaseClass type
     * enabling polymorphic operations on that type using a pre-declared ID
     * 
     * @param id The predefined ID
     * @return New object
     */
    BaseClass* create(const Identifier& id)
    {
        auto findIt = m_creators.find(id);
        if(findIt != m_creators.end())
        {
            ObjectCreator pFunc = findIt->second;
            // Call function
            return pFunc();
        }

        // Null for failed
        return nullptr;
    }

    void remove(const Identifier& id)
    {
        auto findIt = m_creators.find(id);
        CORE_ASSERT(findIt != m_creators.end());

        m_creators.erase(findIt);
    }

    /**
     * @brief Remove all items from factory storage
     */
    void clear()
    {
        //delegate to internal map
        m_creators.clear();
    }

private:
    typedef std::function<BaseClass*(void)> ObjectCreator;
    std::unordered_map<Identifier, ObjectCreator> m_creators;
};

#endif // GENERICOBJECTFACTORY_H
