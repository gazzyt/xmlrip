#ifndef LIBXMLATTRIBUTECOLLECTION_ITERATOR_H
#define LIBXMLATTRIBUTECOLLECTION_ITERATOR_H

#include <iterator>
#include <utility>

#include "libxml/xmlstring.h"

class LibXmlAttributeCollection_iterator
{
public:
	typedef std::input_iterator_tag iterator_category;
	typedef std::pair<const char*, const char*> value_type;
	typedef unsigned int difference_type;
	typedef std::pair<const char*, const char*>* pointer;
	typedef std::pair<const char*, const char*>& reference;

public:
	LibXmlAttributeCollection_iterator() noexcept
		: m_attributes(nullptr), m_npos(MAX_NPOS), m_current(nullptr, nullptr)
	{}

	LibXmlAttributeCollection_iterator(const xmlChar** attributes) noexcept
		:	m_attributes(attributes), m_npos(attributes == nullptr || *attributes == nullptr ? MAX_NPOS : 0)
	{
		if (m_npos == 0)
		{
			m_current = value_type{ reinterpret_cast<const char *>(attributes[0]), reinterpret_cast<const char *>(attributes[1]) };
		}
	}

	LibXmlAttributeCollection_iterator(const LibXmlAttributeCollection_iterator& src) = default;

public:
	const value_type& operator*() const
	{
		return m_current;
	}

	const value_type* operator->() const
	{
		return &m_current;
	}

	LibXmlAttributeCollection_iterator& operator++()
	{
		Increment();
		return *this;
	}

	LibXmlAttributeCollection_iterator operator++(int)
	{
		auto tmp = *this;
		Increment();
		return tmp;
	}

	bool equal(LibXmlAttributeCollection_iterator const& rhs) const
	{
		return (m_npos == rhs.m_npos);
	}

private:
	LibXmlAttributeCollection_iterator operator=(const LibXmlAttributeCollection_iterator& src) = delete;

	void Increment()
	{
		if (m_npos != MAX_NPOS)
		{
			if (m_attributes[m_npos + 2] == nullptr)
			{
				m_npos = MAX_NPOS;
			}
			else
			{
				m_npos+=2;
				m_current.first = reinterpret_cast<const char*>(m_attributes[m_npos]);
				m_current.second = reinterpret_cast<const char*>(m_attributes[m_npos + 1]);
			}
		}
	}

private:
	static constexpr difference_type MAX_NPOS = std::numeric_limits<difference_type>::max();

	const xmlChar** m_attributes;
	difference_type m_npos;
	value_type m_current;
	
};

inline bool operator==(const LibXmlAttributeCollection_iterator& lhs, const LibXmlAttributeCollection_iterator& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const LibXmlAttributeCollection_iterator& lhs, const LibXmlAttributeCollection_iterator& rhs)
{
	return !lhs.equal(rhs);
}
	
#endif
