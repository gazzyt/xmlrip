#ifndef XMLSTREAMMODIFIERS_H
#define XMLSTREAMMODIFIERS_H

#include <iostream>

class XmlStreamModifiers
{
public:
	enum OutputFormat : long {xml = 0L, verbose};

	static std::ostream& XmlFormat(std::ostream &stream);
	static std::ostream& VerboseFormat(std::ostream &stream);
	
	static long GetCurrentOutputFormat(std::ostream &stream);

private:
	static int m_outputFormatIndex;
};

#endif
