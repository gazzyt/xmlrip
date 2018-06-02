#include <cassert>
#include "recordingprinter.h"

using namespace std;

RecordingPrinter::RecordingPrinter()
:	m_items{}
{
}

RecordingPrinter::~RecordingPrinter()
{
}

void RecordingPrinter::StartElement(const char* tagName, LibXmlAttributeCollection attrs)
{
	std::vector<std::pair<std::string, std::string>> attribs;
	
	for (auto iter = begin(attrs); iter != end(attrs); ++iter)
	{
		attribs.push_back(pair<string, string>((char*) iter->first, (char*) iter->second));
	}

	m_items.push_back(RecordingPrinterItem(RecordingPrinterItem::START_ELEMENT, tagName, move(attribs)));
}

void RecordingPrinter::EndElement()
{
	m_items.push_back(RecordingPrinterItem(RecordingPrinterItem::END_ELEMENT, ""));
}

void RecordingPrinter::PrintText(const char* text, int length)
{
	assert(length >= 0);
	m_items.push_back(RecordingPrinterItem{RecordingPrinterItem::TEXT, string{text, static_cast<size_t>(length)}});
}
