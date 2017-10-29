#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>

class XmlElement
{
public:
	enum class Type {tag, declaration, comment};
	enum Format : long {xml = 0L, verbose};
	
	XmlElement() noexcept;
	XmlElement(Type type, std::string tagName, bool isOpeningTag, bool isClosingTag) noexcept;

public:
	XmlElement::Type GetType() const;
	bool IsOpeningTag() const;
	bool IsClosingTag() const;
	std::string GetTagName() const;
	std::string GetAttributeText() const;

	bool operator==(const XmlElement& e1) const;
	bool IsMatch(const XmlElement& e1) const;
	
	static XmlElement FromText(std::string text, bool isOpeningTag, bool isClosingTag);

	void Print(std::ostream& os) const;
	void PrintAsXml(std::ostream& os) const;
	void PrintAsVerbose(std::ostream& os) const;

	static std::ostream& XmlFormat(std::ostream &stream);
	static std::ostream& VerboseFormat(std::ostream &stream);

private:
	XmlElement(Type type, std::string tagName, std::string attributeText, bool isOpeningTag, bool isClosingTag) noexcept;
	
	XmlElement::Type m_type;
	std::string m_tagName;
	std::string m_attributeText;
	bool m_isOpeningTag;
	bool m_isClosingTag;
	static int m_formatIndex;
};

std::ostream& operator<<(std::ostream& os, const XmlElement& elem);

#endif