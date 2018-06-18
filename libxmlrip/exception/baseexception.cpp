#include "exception/baseexception.h"

using namespace std;

BaseException::BaseException(std::string&& message) noexcept
:	m_message(message)
{}

BaseException::~BaseException() noexcept
{}

const char* BaseException::what() const noexcept
{
	return m_message.c_str();
}

