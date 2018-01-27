#include <memory>

#include "exception/printexception.h"

using namespace std;

PrintException::PrintException(std::string&& message) noexcept
:	BaseException(move(message))
{}

