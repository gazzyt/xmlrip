#ifndef RECORDINGPRINTERITEM_H
#define RECORDINGPRINTERITEM_H

#include "libxmlattributecollection.h"

class RecordingPrinterItem
{
public:
	enum ItemType { START_ELEMENT, END_ELEMENT, TEXT };
	
public:
	RecordingPrinterItem(ItemType type, const std::string& text) : m_type{type}, m_text{text} {}
	RecordingPrinterItem(const RecordingPrinterItem& rhs) = default;
	
	RecordingPrinterItem& operator=(const RecordingPrinterItem& rhs) = delete;
	
	bool operator==(const RecordingPrinterItem& rhs) const { return (m_type == rhs.m_type) && (m_text == rhs.m_text); }
	bool operator!=(const RecordingPrinterItem& rhs) const { return !(*this == rhs); }

	const std::string& GetText() const { return m_text; }
	ItemType GetType() const { return m_type; }
	
private:
	ItemType m_type;
	std::string m_text;
};

#endif
