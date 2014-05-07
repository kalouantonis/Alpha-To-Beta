#ifndef LOCATOR_H
#define LOCATOR_H

#include <assert.h>
#include <memory>

template <class T>
class Locator
{
public:
	typedef std::shared_ptr<T> Ptr;

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

template <class T>
/**
 * @brief Create object that will not be deleted by locator
 * @param p
 * @return
 */
inline std::shared_ptr<T> void_deleter_ptr(T* p)
{
    // Void deleter lambda
    return std::shared_ptr<T>(p, [](T* p) {});
}

#endif // LOCATOR_H
