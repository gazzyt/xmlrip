#ifndef CUSTOMPRINTERS_H
#define CUSTOMPRINTERS_H

#include <iostream>

#include "xmlelement.h"
#include "xmlattribute.h"
#include "recordingprinteritem.h"

inline void PrintTo(const XmlElement& elem, ::std::ostream* os)
{
  elem.PrintAsVerbose(*os);
}

inline void PrintTo(const XmlAttribute& attr, ::std::ostream* os)
{
  attr.PrintAsVerbose(*os);
}

inline void PrintTo(const RecordingPrinterItem& item, ::std::ostream* os)
{
	*os << "{ " << item.GetType() << ", \"" << item.GetText() << "\" }";
}

#endif