#include "customstreamflags.h"

using namespace std;

int CustomStreamFlags::CreateFlag()
{
	return ios_base::xalloc();
}

long& CustomStreamFlags::GetIWordValue(ios_base& ios, int index)
{
	return ios.iword(index);
}

void CustomStreamFlags::SetIWordValue(std::ios_base& ios, int index, long value)
{
	GetIWordValue(ios, index) = value;
}