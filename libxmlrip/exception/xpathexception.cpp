#include <memory>

#include "exception/xpathexception.h"

using namespace std;

XPathException::XPathException(std::string&& message) noexcept
:	BaseException(move(message))
{}

