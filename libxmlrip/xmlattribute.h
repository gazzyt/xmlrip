#ifndef XMLATTRIBUTE_H
#define XMLATTRIBUTE_H

#include <string>

class XmlAttribute
{
public:
	enum Format : long {xml = 0L, verbose};
	
	XmlAttribute(std::string&& attrName, std::string&& attrValue) noexcept;

public:
	const std::string& GetName() const;
	const std::string& GetValue() const;

	bool operator==(const XmlAttribute& rhs) const;
	
	void Print(std::ostream& os) const;
	void PrintAsXml(std::ostream& os) const;
	void PrintAsVerbose(std::ostream& os) const;


private:
	std::string m_name;
	std::string m_value;
};

std::ostream& operator<<(std::ostream& os, const XmlAttribute& attrib);

#endif