#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <ostream>
#include <string>

class BaseException : public std::exception
{
public:
	BaseException(std::string&& message) noexcept;
	virtual ~BaseException() noexcept;

	virtual void Print(std::ostream& os) const;
	virtual const char* what() const noexcept;

private:
	std::string m_message;
};

std::ostream& operator<<(std::ostream& os, const BaseException& exception);

#endif