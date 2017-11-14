#ifndef CUSTOMPRINTERS_H
#define CUSTOMPRINTERS_H

#include <iostream>

#include "xmlelement.h"
#include "xmlattribute.h"

inline void PrintTo(const XmlElement& elem, ::std::ostream* os)
{
  elem.PrintAsVerbose(*os);
}

inline void PrintTo(const XmlAttribute& attr, ::std::ostream* os)
{
  attr.PrintAsVerbose(*os);
}


#endif