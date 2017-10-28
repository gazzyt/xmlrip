#ifndef XMLELEMENTREADER_ITERATOR_H
#define XMLELEMENTREADER_ITERATOR_H

#include <iterator>

#include "xmlelementreader.h"

class XmlElementReader_iterator
	: public std::iterator<std::input_iterator_tag, XmlElement, std::ptrdiff_t, const XmlElement*, const XmlElement&>
{
public:
	XmlElementReader_iterator() noexcept;
	XmlElementReader_iterator(XmlElementReader& reader);
	XmlElementReader_iterator(const XmlElementReader_iterator& src);

public:
	const XmlElement& operator*() const;
    const XmlElement* operator->() const;
	XmlElementReader_iterator& operator++();
	XmlElementReader_iterator operator++(int);
	bool equal(XmlElementReader_iterator const& rhs) const;

private:
	XmlElementReader_iterator operator=(const XmlElementReader_iterator& src) = delete;
	
	void Read();
	
	XmlElementReader* m_reader;
	XmlElement m_value;
	bool m_ok;
	
};

inline bool operator==(const XmlElementReader_iterator& lhs, const XmlElementReader_iterator& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const XmlElementReader_iterator& lhs, const XmlElementReader_iterator& rhs)
{
	return !lhs.equal(rhs);
}
	
#endif
