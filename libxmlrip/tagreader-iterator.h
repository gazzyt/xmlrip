#ifndef TAGREADER_ITERATOR_H
#define TAGREADER_ITERATOR_H

#include <iterator>

#include "tagreader.h"

class TagReader_iterator
	: public std::iterator<std::input_iterator_tag, Tag, std::ptrdiff_t, const Tag*, const Tag&>
{
public:
	TagReader_iterator() noexcept;
	TagReader_iterator(TagReader& reader);
	TagReader_iterator(const TagReader_iterator& src);

public:
	const Tag& operator*() const;
    const Tag* operator->() const;
	TagReader_iterator& operator++();
	TagReader_iterator operator++(int);
	bool equal(TagReader_iterator const& rhs) const;

private:
	TagReader_iterator operator=(const TagReader_iterator& src) = delete;
	
	void Read();
	
	TagReader* m_reader;
	Tag m_value;
	bool m_ok;
	
};

inline bool operator==(const TagReader_iterator& lhs, const TagReader_iterator& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const TagReader_iterator& lhs, const TagReader_iterator& rhs)
{
	return !lhs.equal(rhs);
}
	
#endif
