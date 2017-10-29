#ifndef CUSTOMSTREAMFLAGS_H
#define CUSTOMSTREAMFLAGS_H

#include <iostream>

class CustomStreamFlags
{
public:
	static int CreateFlag();
	static long& GetIWordValue(std::ios_base& ios, int index);
	static void SetIWordValue(std::ios_base& ios, int index, long value);

};

#endif
