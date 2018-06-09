#include "exception/baseexception.h"

using namespace std;

BaseException::BaseException(std::string&& message) noexcept
:	m_message(message)
{}

BaseException::~BaseException() noexcept
{}

void BaseException::Print(std::ostream& os) const
{
	os << m_message;
}

const char* BaseException::what() const noexcept
{
	return m_message.c_str();
}

ostream& operator<<(ostream& os, const BaseException& exception)
{
	exception.Print(os);
	
	return os;
}

