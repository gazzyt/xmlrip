#ifndef XPATHREADER_H
#define XPATHREADER_H

#include <memory>

#include "xmlexpression.h"
#include "xmlstepexpr.h"
#include "xmlattributepredicate.h"

class XPathReader
{
public:
	XPathReader() = delete;
	XPathReader(const XPathReader& rhs) = delete;

public:
	XPathReader& operator=(const XPathReader& rhs) = delete;
	
	static std::unique_ptr<XmlExpression> FromText(const std::string& text);
	static std::unique_ptr<XmlStepExpr> ReadStepExpr(XPathTokeniser& tokeniser, XPathToken& token);
	static std::unique_ptr<XmlAttributePredicate> ReadAttributePredicate(XPathTokeniser& tokeniser, XPathToken& token);
	
};

#endif
