
#include "tagreader-iterator.h"

TagReader_iterator::TagReader_iterator() noexcept
:	m_reader{nullptr}, m_value{}, m_ok{false}
{}
	
TagReader_iterator::TagReader_iterator(TagReader& reader)
:	m_reader{&reader}, m_value{}, m_ok{true}
{
	Read();
}

TagReader_iterator::TagReader_iterator(const TagReader_iterator& src)
:	m_reader{src.m_reader}, m_value{src.m_value}, m_ok{src.m_ok}
{}

const Tag& TagReader_iterator::operator*() const
{
	return m_value;
}

const Tag* TagReader_iterator::operator->() const
{
	return &m_value;
}

TagReader_iterator& TagReader_iterator::operator++()
{
	Read();
	return *this;
}

TagReader_iterator TagReader_iterator::operator++(int)
{
	auto tmp = *this;
	Read();
	return tmp;
}

bool TagReader_iterator::equal(TagReader_iterator const& rhs) const
{
	return (m_ok == rhs.m_ok) && (!m_ok || m_reader == rhs.m_reader);
}

void TagReader_iterator::Read()
{
	m_ok = m_ok && m_reader;
	
	if(m_ok)
	{
		m_value = m_reader->GetNextTag();
		m_ok = m_value.GetTagName() != "EOF";
	}
}
