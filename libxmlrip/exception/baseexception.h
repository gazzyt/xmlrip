#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <ostream>
#include <string>

class BaseException
{
public:
	BaseException(std::string&& message) noexcept;
	virtual ~BaseException() noexcept;

	virtual const std::string& GetMessage() const;
	virtual void Print(std::ostream& os) const;

private:
	std::string m_message;
};

std::ostream& operator<<(std::ostream& os, const BaseException& exception);

#endif