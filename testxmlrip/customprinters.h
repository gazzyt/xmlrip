#ifndef CUSTOMPRINTERS_H
#define CUSTOMPRINTERS_H

#include <iostream>

#include "xmlelement.h"

inline void PrintTo(const XmlElement& elem, ::std::ostream* os)
{
  elem.PrintAsVerbose(*os);
}


#endif