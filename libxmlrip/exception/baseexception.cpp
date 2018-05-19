#include "exception/baseexception.h"

using namespace std;

BaseException::BaseException(std::string&& message) noexcept
:	m_message(message)
{}

BaseException::~BaseException() noexcept
{}

const string& BaseException::GetMessage() const
{
	return m_message;
}

void BaseException::Print(std::ostream& os) const
{
	os << m_message;
}

ostream& operator<<(ostream& os, const BaseException& exception)
{
	exception.Print(os);
	
	return os;
}
