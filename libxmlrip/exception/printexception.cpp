#include <memory>

#include "exception/printexception.h"

using namespace std;

PrintException::PrintException(string message) noexcept
:	BaseException(message)
{}

