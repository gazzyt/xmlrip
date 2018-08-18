#ifndef RESETTINGPTR_H
#define RESETTINGPTR_H

#include <cassert>

template <class T> class ResettingPtr
{
public:
	ResettingPtr();
	ResettingPtr(const ResettingPtr& rhs) = delete;
	const ResettingPtr& operator=(const ResettingPtr& rhs) = delete;

public:
	const ResettingPtr<T>& operator=(T* ptr);
	T* operator->() const;
	
private:
	T* m_ptr;

};


template <class T>
ResettingPtr<T>::ResettingPtr()
:	m_ptr{nullptr}
{
}

template<class T>
const ResettingPtr<T>& ResettingPtr<T>::operator=(T* ptr)
{
	m_ptr = ptr;
	
	if (ptr)
	{
		ptr->Reset();
	}
	
	return *this;
}

template<class T>
T* ResettingPtr<T>::operator->() const
{
	return m_ptr;
}

#endif
