#include <sstream>

#include "exception/xpathexception.h"

using namespace std;

XPathException::XPathException(string message, int position) noexcept
:	BaseException(message),
	m_position(position)
{
	ostringstream oss;
	oss << " at position " << position;
	m_message += oss.str();
}

int XPathException::GetPosition() const
{
	return m_position;
}
