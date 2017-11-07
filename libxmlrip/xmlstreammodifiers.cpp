#include "customstreamflags.h"
#include "xmlstreammodifiers.h"

using namespace std;

int XmlStreamModifiers::m_outputFormatIndex = CustomStreamFlags::CreateFlag();

ostream& XmlStreamModifiers::XmlFormat(ostream &stream)
{
	CustomStreamFlags::SetIWordValue(stream, m_outputFormatIndex, OutputFormat::xml);
	return(stream);
}

ostream& XmlStreamModifiers::VerboseFormat(ostream &stream)
{
	CustomStreamFlags::SetIWordValue(stream, m_outputFormatIndex, OutputFormat::verbose);
	return(stream);
}

long XmlStreamModifiers::GetCurrentOutputFormat(std::ostream &stream)
{
	return CustomStreamFlags::GetIWordValue(stream, m_outputFormatIndex);
}

