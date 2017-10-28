#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>

class XmlElement
{
public:
	XmlElement() noexcept;
	XmlElement(std::string tagName, bool isOpeningTag, bool isClosingTag) noexcept;

public:
	bool IsOpeningTag() const;
	bool IsClosingTag() const;
	std::string GetTagName() const;
	std::string GetAttributeText() const;

	bool operator==(const XmlElement& e1) const;
	bool IsMatch(const XmlElement& e1) const;
	
	static XmlElement FromText(std::string text, bool isOpeningTag, bool isClosingTag);

private:
	XmlElement(std::string tagName, std::string attributeText, bool isOpeningTag, bool isClosingTag) noexcept;
	
	std::string m_tagName;
	std::string m_attributeText;
	bool m_isOpeningTag;
	bool m_isClosingTag;
};

std::ostream& operator<<(std::ostream& os, const XmlElement& elem);

#endif