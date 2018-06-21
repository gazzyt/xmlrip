#include <sstream>

#include "exception/xpathexception.h"

using namespace std;

XPathException::XPathException(string message, int position) noexcept
:	BaseException(message)
{
	ostringstream oss;
	oss << " at position " << position;
	m_message += oss.str();
}

