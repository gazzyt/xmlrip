#include "porting.h"

#ifdef WIN32
#include <stdio.h>
#else
#include <unistd.h>
#endif // WIN32

using namespace std;

int Porting::StdOutFileNo()
{
#ifdef WIN32
	return _fileno(stdout);
#else
	return STDOUT_FILENO;
#endif // WIN32

}
