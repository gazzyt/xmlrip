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
	m_items.push_back(RecordingPrinterItem(RecordingPrinterItem::START_ELEMENT, tagName));
}

void RecordingPrinter::EndElement()
{
	m_items.push_back(RecordingPrinterItem(RecordingPrinterItem::END_ELEMENT, ""));
}

void RecordingPrinter::PrintText(const char* text, int length)
{
	m_items.push_back(RecordingPrinterItem{RecordingPrinterItem::TEXT, string{text, length}});
}
