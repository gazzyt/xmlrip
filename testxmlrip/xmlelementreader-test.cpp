#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>

#include "xmlelementreader.h"
#include "customprinters.h"

using namespace std;

template <class ELEMSTYPE> static void TextToElementsTestHelper(const string& xmlText, const ELEMSTYPE& expectedElements);

static const string simpleXml = "<a></a>";
static const auto simpleXmlElements = {
	XmlElement{XmlElement::Type::tag, "a", true, false}, 
	XmlElement{XmlElement::Type::tag, "a", false, true}
};

static const string simpleXmlWithLineBreaks = "<a>\n</a>\n";
static const auto simpleXmlWithLineBreaksElements = {
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
	TextToElementsTestHelper(simpleXml, simpleXmlElements);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithDeclaration) {
	TextToElementsTestHelper(simpleXmlWithDeclaration, simpleXmlWithDeclarationElements);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithComment) {
	TextToElementsTestHelper(simpleXmlWithComment, simpleXmlWithCommentElements);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithText) {
	TextToElementsTestHelper(simpleXmlWithText, simpleXmlWithTextElements);
}

TEST(XmlElementReader, CreatesCorrectElementsForSimpleXmlWithLineBreaks) {
	TextToElementsTestHelper(simpleXmlWithLineBreaks, simpleXmlWithLineBreaksElements);
}

template <class ELEMSTYPE> static void TextToElementsTestHelper(const string& xmlText, const ELEMSTYPE& expectedElements) {
	int elementIndex = 0;
	auto buf = make_unique<InlineBuffer>( make_unique<istringstream>(xmlText), 10 );
	XmlElementReader elementReader{ move(buf) };

	for_each(begin(expectedElements), end(expectedElements), 
		[&] (const XmlElement& elem) 
		{
			EXPECT_EQ(elem, elementReader.GetNextElement()) << "Element number " << elementIndex << " did not have expected value";
			++elementIndex;
		}
	);
}
