#ifndef XMLATTRIBUTEPREDICATE_H
#define XMLATTRIBUTEPREDICATE_H

#include <string>

#include "xmlattribute.h"

class XmlAttributePredicate
{
public:
	enum Mode {MODE_EQUAL, MODE_STARTSWITH};
	XmlAttributePredicate(Mode mode, std::string&& attrName, std::string&& attrValue) noexcept;

public:
	Mode GetMode() const;
	const std::string& GetName() const;
	const std::string& GetValue() const;

	bool IsMatch(const char* name, const char* value) const noexcept;
	template<class T> bool IsMatch(const T& attributes) const noexcept;

private:
	Mode m_mode;
	std::string m_name;
	std::string m_value;
};

template<class T> bool XmlAttributePredicate::IsMatch(const T& attributes) const noexcept
{
	for (auto attribute : attributes)
	{
		if (IsMatch(attribute.first, attribute.second))
		{
			return true;
		}
	}
	return false;
}

#endif