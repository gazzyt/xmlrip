#ifndef LIBXMLUTILS_H
#define LIBXMLUTILS_H

#include <cctype>

#include "libxml/parser.h"

bool isspace(const xmlChar *chars, int len);

#endif