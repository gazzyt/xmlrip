#include <algorithm>
#include <cctype>
#include "libxmlutils.h"

using namespace std;

bool isspace(const xmlChar *chars, int len)
{
	const char *theChars = reinterpret_cast<const char*>(chars);
	
	return all_of(theChars, theChars + len, [](char c){return isspace(c);});
}
