#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <vector>

#include "xmlattribute.h"

class XmlElement
{
public:
	enum class Type {tag, declaration, comment, text};
	
	XmlElement() noexcept;
	XmlElement(Type type, std::string tagName, bool isOpeningTag, bool isClosingTag) noexcept;
	XmlElement(Type type, std::string tagName, std::vector<XmlAttribute>&& attributes, bool isOpeningTag, bool isClosingTag) noexcept;

public:
	XmlElement::Type GetType() const;
	bool IsOpeningTag() const;
	bool IsClosingTag() const;
	const std::string& GetTagName() const;
	std::string GetAttributeText() const;
	const std::string* GetAttributeValue(const std::string& attrName) const;

	bool operator==(const XmlElement& e1) const;
	bool IsMatch(const XmlElement& e1) const;
	
	static XmlElement FromText(std::string text, bool isOpeningTag, bool isClosingTag);

	void Print(std::ostream& os) const;
	void PrintAsXml(std::ostream& os) const;
	void PrintAsVerbose(std::ostream& os) const;


private:
	static std::vector<XmlAttribute> ReadAttributes(std::string text);
	
	XmlElement::Type m_type;
	std::string m_tagName;
	std::vector<XmlAttribute> m_attributes;
	bool m_isOpeningTag;
	bool m_isClosingTag;
};

std::ostream& operator<<(std::ostream& os, const XmlElement& elem);

#endif