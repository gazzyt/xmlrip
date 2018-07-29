#ifndef XMLATTRIBUTEPREDICATE_H
#define XMLATTRIBUTEPREDICATE_H

#include <string>

#include "xmlattribute.h"
#include "xmlpredicate.h"
#include "libxmlattributecollection.h"
#include "libxmlattributecollection-iterator.h"

class XmlAttributePredicate : public XmlPredicate
{
public:
	enum Mode {MODE_EQUAL, MODE_STARTSWITH};
	XmlAttributePredicate(Mode mode, std::string&& attrName, std::string&& attrValue) noexcept;

public:
	Mode GetMode() const;
	const std::string& GetName() const;
	const std::string& GetValue() const;

	bool IsMatch(const char* name, const char* value) const noexcept;
	virtual bool IsMatch(const LibXmlAttributeCollection& attributes) const noexcept;

private:
	Mode m_mode;
	std::string m_name;
	std::string m_value;
};

#endif