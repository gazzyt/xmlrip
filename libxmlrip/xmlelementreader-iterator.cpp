
#include "xmlelementreader-iterator.h"

XmlElementReader_iterator::XmlElementReader_iterator() noexcept
:	m_reader{nullptr}, m_value{}, m_ok{false}
{}
	
XmlElementReader_iterator::XmlElementReader_iterator(XmlElementReader& reader)
:	m_reader{&reader}, m_value{}, m_ok{true}
{
	Read();
}

XmlElementReader_iterator::XmlElementReader_iterator(const XmlElementReader_iterator& src)
:	m_reader{src.m_reader}, m_value{src.m_value}, m_ok{src.m_ok}
{}

const XmlElement& XmlElementReader_iterator::operator*() const
{
	return m_value;
}

const XmlElement* XmlElementReader_iterator::operator->() const
{
	return &m_value;
}

XmlElementReader_iterator& XmlElementReader_iterator::operator++()
{
	Read();
	return *this;
}

XmlElementReader_iterator XmlElementReader_iterator::operator++(int)
{
	auto tmp = *this;
	Read();
	return tmp;
}

bool XmlElementReader_iterator::equal(XmlElementReader_iterator const& rhs) const
{
	return (m_ok == rhs.m_ok) && (!m_ok || m_reader == rhs.m_reader);
}

void XmlElementReader_iterator::Read()
{
	m_ok = m_ok && m_reader;
	
	if(m_ok)
	{
		m_value = m_reader->GetNextElement();
		m_ok = m_value.GetTagName() != "EOF";
	}
}
