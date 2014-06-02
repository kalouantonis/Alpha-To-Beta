#ifndef LOCATOR_H
#define LOCATOR_H

#include <assert.h>
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
		return m_sObject;
	}

	static void provide(Ptr object)
	{
		m_sObject = object;
	}

	static void remove()
	{
		m_sObject = nullptr;
	}

private:
	static Ptr m_sObject;	
};

// Initialize object
template <class T>
std::shared_ptr<T> Locator<T>::m_sObject = nullptr;

#endif // LOCATOR_H
