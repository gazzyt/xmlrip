#ifndef RECORDINGPRINTERITEM_H
#define RECORDINGPRINTERITEM_H

#include "libxmlattributecollection.h"

class RecordingPrinterItem
{
public:
	enum ItemType { START_ELEMENT, END_ELEMENT, TEXT, CDATA };
	
public:
	RecordingPrinterItem(ItemType type, const std::string& text)
	:	m_type{type}, m_text{text}, m_attribs{} {}
	RecordingPrinterItem(ItemType type, const std::string& text, const std::vector<std::pair<std::string, std::string>>& attribs)
	:	m_type{type}, m_text{text}, m_attribs{attribs} {}
	RecordingPrinterItem(ItemType type, const std::string& text, std::vector<std::pair<std::string, std::string>>&& attribs)
	:	m_type{type}, m_text{text}, m_attribs{attribs} {}
	RecordingPrinterItem(const RecordingPrinterItem& rhs) = default;
	
	RecordingPrinterItem& operator=(const RecordingPrinterItem& rhs) = delete;
	
	bool operator==(const RecordingPrinterItem& rhs) const { return (m_type == rhs.m_type) && (m_text == rhs.m_text); }
	bool operator!=(const RecordingPrinterItem& rhs) const { return !(*this == rhs); }

	const std::string& GetText() const { return m_text; }
	ItemType GetType() const { return m_type; }
	const std::vector<std::pair<std::string, std::string>>& GetAttributes() const { return m_attribs; }
	
private:
	ItemType m_type;
	std::string m_text;
	std::vector<std::pair<std::string, std::string>> m_attribs;
};

#endif
