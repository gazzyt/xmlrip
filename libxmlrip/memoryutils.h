#ifndef MEMORYUTILS_H
#define MEMORYUTILS_H

#include <memory>

template< class T > std::unique_ptr<T> copy_unique(const std::unique_ptr<T>& source)
{
	return source ? std::make_unique<T>(*source) : nullptr;
}

#endif