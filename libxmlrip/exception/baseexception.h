#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <ostream>
#include <string>

class BaseException : public std::exception
{
public:
	BaseException(std::string message) noexcept;
	virtual ~BaseException() noexcept;

	virtual const char* what() const noexcept;

protected:
	std::string m_message;
};


#endif