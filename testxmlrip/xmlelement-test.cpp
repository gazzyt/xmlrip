#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <sstream>

#include "xmlstreammodifiers.h"
#include "customprinters.h"
#include "libxmlattributecollection.h"

#include "xmlelement.h"

using namespace std;

/******************************************************************************************/
/* FromText tests */
/******************************************************************************************/

TEST(XmlElement, CreatesCorrectElementFromNameOnly) {
	// Arrange
	string tagText{"aa"};
	
	// Act
	XmlElement element = XmlElement::FromText(tagText, true, true);
	
	// Assert
	EXPECT_TRUE(element.IsOpeningTag());
	EXPECT_TRUE(element.IsClosingTag());
	EXPECT_EQ("aa", element.GetTagName());
}


/******************************************************************************************/
/* constructor tests */
/******************************************************************************************/

TEST(XmlElement, CreatesCorrectElementFromNameAndLibXmlAttributes) {
	// Arrange
	string tagName = "aa";
	static const xmlChar* testStrings[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2", nullptr };
	LibXmlAttributeCollection attrs{ testStrings };

	// Act
	XmlElement element{ XmlElement::Type::tag, tagName, attrs, true, false };

	// Assert
	EXPECT_TRUE(element.IsOpeningTag());
	EXPECT_FALSE(element.IsClosingTag());
	EXPECT_EQ("aa", element.GetTagName());
	EXPECT_EQ("attname1=\"attvalue1\" attname2=\"attvalue2\"", element.GetAttributeText());
}

/******************************************************************************************/
/* GetAttributeValue tests */
/******************************************************************************************/

TEST(XmlElement, GetAttributeValueReturnsCorrectValueWhenAttributeExists) {
	// Arrange
	vector<XmlAttribute> attrs = {XmlAttribute{"at1", "at1value"}};
	auto elem = XmlElement{XmlElement::Type::tag, "a", move(attrs), true, false};
	
	// Act
	auto attrValue = elem.GetAttributeValue("at1");
	
	// Assert
	ASSERT_TRUE(attrValue != nullptr);
	EXPECT_EQ("at1value", *attrValue);
}

TEST(XmlElement, GetAttributeValueReturnsNullWhenAttributeDoesNotExist) {
	// Arrange
	vector<XmlAttribute> attrs = {XmlAttribute{"at1", "at1value"}};
	auto elem = XmlElement{XmlElement::Type::tag, "a", move(attrs), true, false};
	
	// Act
	auto attrValue = elem.GetAttributeValue("at2");
	
	// Assert
	ASSERT_TRUE(attrValue == nullptr);
}

/******************************************************************************************/
/* stream insertion tests */
/******************************************************************************************/

TEST(XmlElement, PrintsAsXmlByDefault)
{
	// Arrange
	XmlElement element{XmlElement::Type::tag, "aa", true, false};
	ostringstream stream;
	
	// Act
	stream << element << endl;
	
	// Assert
	EXPECT_EQ('<', stream.str()[0]);
}

TEST(XmlElement, PrintsAsXml)
{
	// Arrange
	vector<XmlAttribute> attrs = {XmlAttribute{"at1", "987"}};
	auto element = XmlElement{XmlElement::Type::tag, "aa", move(attrs), true, false};
	ostringstream stream;
	stream << XmlStreamModifiers::XmlFormat;
	
	// Act
	stream << element;
	
	// Assert
#ifdef USE_INTERNAL_PARSER
	EXPECT_EQ("<aa at1=987>", stream.str());
#else
	EXPECT_EQ("<aa at1=\"987\">", stream.str());
#endif
}

TEST(XmlElement, PrintsAsXmlWithNoAttributes)
{
	// Arrange
	auto element = XmlElement{XmlElement::Type::tag, "aa", true, false};
	ostringstream stream;
	stream << XmlStreamModifiers::XmlFormat;
	
	// Act
	stream << element;
	
	// Assert
	EXPECT_EQ("<aa>", stream.str());
}

TEST(XmlElement, PrintsAsVerbose)
{
	// Arrange
	XmlElement element{XmlElement::Type::tag, "aa", true, false};
	ostringstream stream;
	stream << XmlStreamModifiers::VerboseFormat;
	
	// Act
	stream << element << endl;
	
	// Assert
	EXPECT_EQ('{', stream.str()[0]);
}