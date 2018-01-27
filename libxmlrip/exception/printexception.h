#ifndef PRINTEXCEPTION_H
#define PRINTEXCEPTION_H

#include "exception/baseexception.h"

class PrintException : public BaseException
{
public:
	PrintException(std::string&& message) noexcept;

};

#endif