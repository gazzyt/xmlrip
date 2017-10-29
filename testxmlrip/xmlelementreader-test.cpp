#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "xmlelementreader.h"
#include "customprinters.h"

using namespace std;

static const string simpleXml = "<a></a>";
static const auto simpleXmlElements = {
	XmlElement{XmlElement::Type::tag, "a", true, false}, 
	XmlElement{XmlElement::Type::tag, "a", false, true}
};

static const string simpleXmlWithDeclaration = "<?xml version=\"1.0\"?><a></a>";
static const auto simpleXmlWithDeclarationElements = {
	XmlElement{XmlElement::Type::declaration, "xml version=\"1.0\"", true, true}, 
	XmlElement{XmlElement::Type::tag, "a", true, false},
	XmlElement{XmlElement::Type::tag, "a", false, true}
};

static const string simpleXmlWithComment = "<a><!--comment--></a>";
static const auto simpleXmlWithCommentElements = {
	XmlElement{XmlElement::Type::tag, "a", true, false}, 
	XmlElement{XmlElement::Type::comment, "comment", true, true}, 
	XmlElement{XmlElement::Type::tag, "a", false, true}
};

static const string simpleXmlWithText = "<a>Some text</a>";
static const auto simpleXmlWithTextElements = {
	XmlElement{XmlElement::Type::tag, "a", true, false}, 
	XmlElement{XmlElement::Type::text, "Some text", true, true}, 
	XmlElement{XmlElement::Type::tag, "a", false, true}
};

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXml) {
	int elementIndex = 0;
	auto xmlStream = make_unique<istringstream>(simpleXml);
	XmlElementReader elementReader{move(xmlStream)};
	
	for_each(begin(simpleXmlElements), end(simpleXmlElements), 
		[&] (const XmlElement& elem) 
		{
			EXPECT_EQ(elem, elementReader.GetNextElement()) << "Element number " << elementIndex << " did not have expected value";
			++elementIndex;
		}
	);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithDeclaration) {
	int elementIndex = 0;
	auto xmlStream = make_unique<istringstream>(simpleXmlWithDeclaration);
	XmlElementReader elementReader{move(xmlStream)};
	
	for_each(begin(simpleXmlWithDeclarationElements), end(simpleXmlWithDeclarationElements), 
		[&] (const XmlElement& elem) 
		{
			EXPECT_EQ(elem, elementReader.GetNextElement()) << "Element number " << elementIndex << " did not have expected value";
			++elementIndex;
		}
	);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithComment) {
	int elementIndex = 0;
	auto xmlStream = make_unique<istringstream>(simpleXmlWithComment);
	XmlElementReader elementReader{move(xmlStream)};
	
	for_each(begin(simpleXmlWithCommentElements), end(simpleXmlWithCommentElements), 
		[&] (const XmlElement& elem) 
		{
			EXPECT_EQ(elem, elementReader.GetNextElement()) << "Element number " << elementIndex << " did not have expected value";
			++elementIndex;
		}
	);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithText) {
	int elementIndex = 0;
	auto xmlStream = make_unique<istringstream>(simpleXmlWithText);
	XmlElementReader elementReader{move(xmlStream)};
	
	for_each(begin(simpleXmlWithTextElements), end(simpleXmlWithTextElements), 
		[&] (const XmlElement& elem) 
		{
			EXPECT_EQ(elem, elementReader.GetNextElement()) << "Element number " << elementIndex << " did not have expected value";
			++elementIndex;
		}
	);
}
