#ifndef XPATHEXCEPTION_H
#define XPATHEXCEPTION_H

#include "exception/baseexception.h"

class XPathException : public BaseException
{
public:
	XPathException(std::string message, int position) noexcept;
	
public:
	int GetPosition() const;
	
private:
	int m_position;

};

#endif