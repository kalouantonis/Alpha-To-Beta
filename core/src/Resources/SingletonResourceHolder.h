#ifndef SINGLETONRESOURCEHOLDER_H
#define SINGLETONRESOURCEHOLDER_H

#include <Resources/SharedResourceHolder.h>
#include <SFML/System/NonCopyable.hpp>

/**
 * @brief Singleton containing resources.
 *
 * Should be cleared, but should also clear itself when destructed
 */
template <class Identifier, class Resource>
class SingletonResouceHolder
        : public SharedResourceHolder<Identifier, Resource>
        // Disable copying
        , private sf::NonCopyable
{
public:
    /**
     * @brief Request the current instance of the texture holder
     * @return Instance of texture holder
     */
    static SingletonResouceHolder& instance()
    {
        static SingletonResouceHolder<Identifier, Resource> instance;
        return instance;
    }

protected:
    // disable constructor
    SingletonResouceHolder() {}
};


typedef SingletonResouceHolder<std::string, sf::Texture> SingletonTextureHolder;

#endif // SINGLETONRESOURCEHOLDER_H
