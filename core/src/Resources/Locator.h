#ifndef LOCATOR_H
#define LOCATOR_H

#include <Utils/Logger.h>
#include <memory>

/**
 * @brief Locator pattern. 
 * @details See http://gameprogrammingpatterns.com/service-locator.html for more details
 * 
 * @tparam T Type stored in locator
 */
template <class T>
class Locator
{
public:
	typedef std::shared_ptr<T> Ptr;

	/**
	 * @brief Get object reference
	 */
	static Ptr getObject() 
	{
		CORE_ASSERT(s_pObject != nullptr);
		return s_pObject;
	}

	/**
	 * Provide new object to locator. Will overwrite the previous one
     */
	static void provide(Ptr object)
	{
		s_pObject = object;
	}

	/**
	 * Remove object from locator, will be de-allocated once all references 
	 * are deleted
     */
	static void remove()
	{
		s_pObject = nullptr;
	}

private:
	static Ptr s_pObject;	
};

// Initialize object
template <class T>
std::shared_ptr<T> Locator<T>::s_pObject = nullptr;

#endif // LOCATOR_H
