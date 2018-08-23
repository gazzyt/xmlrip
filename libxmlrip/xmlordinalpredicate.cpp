#include <cstring>
#include <ostream>

#include "xmlstreammodifiers.h"

#include "xmlordinalpredicate.h"

using namespace std;

XmlOrdinalPredicate::XmlOrdinalPredicate(unsigned int ordinal) noexcept
	: m_ordinal{ordinal}, m_count{0U}
{}

unsigned int XmlOrdinalPredicate::GetOrdinal() const
{
	return m_ordinal;
}

void XmlOrdinalPredicate::Reset()
{
	m_count = 0U;
}

bool XmlOrdinalPredicate::IsMatch(const LibXmlAttributeCollection& /*attributes*/) noexcept
{
	return (++m_count == m_ordinal);
}
