#ifndef RECORDINGPRINTER_H
#define RECORDINGPRINTER_H

#include <vector>

#include "recordingprinteritem.h"
#include "libxmlattributecollection.h"

class RecordingPrinter
{
public:
	RecordingPrinter();
	RecordingPrinter(const RecordingPrinter& rhs) = delete;
	~RecordingPrinter();
	
	RecordingPrinter& operator=(const RecordingPrinter& rhs) = delete;

	void StartElement(const char* tagName, LibXmlAttributeCollection attrs);
	void EndElement();
	void PrintText(const char* text, int length);
	void PrintCData(const char* text, int length);
	
	const std::vector<RecordingPrinterItem>& GetRecordedItems() const { return m_items; }
	
private:
	std::vector<RecordingPrinterItem> m_items;
};

#endif
