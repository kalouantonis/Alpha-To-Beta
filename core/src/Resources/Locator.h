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
		// Make sure we arent returning a null object
		assert(m_sObject != nullptr);
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