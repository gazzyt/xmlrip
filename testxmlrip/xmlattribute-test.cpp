#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <sstream>

#include "xmlstreammodifiers.h"
#include "customprinters.h"

#include "xmlattribute.h"

using namespace std;


TEST(XmlAttribute, CreatesCorrectAttribute) {
	// Arrange
	
	// Act
	XmlAttribute attribute("aname", "avalue");
	
	// Assert
	EXPECT_EQ("aname", attribute.GetName());
	EXPECT_EQ("avalue", attribute.GetValue());
}

TEST(XmlAttribute, AttributesNotEqualWhenAttributeNameDiffers) {
	// Arrange
	XmlAttribute attribute1("aname", "avalue");
	XmlAttribute attribute2("bname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(attribute1 == attribute2);
}

TEST(XmlAttribute, AttributesNotEqualWhenAttributeValueDiffers) {
	// Arrange
	XmlAttribute attribute1("aname", "avalue");
	XmlAttribute attribute2("aname", "bvalue");
	
	// Act
	
	// Assert
	EXPECT_FALSE(attribute1 == attribute2);
}

TEST(XmlAttribute, AttributesEqualWhenNameAndValueSame) {
	// Arrange
	XmlAttribute attribute1("aname", "avalue");
	XmlAttribute attribute2("aname", "avalue");
	
	// Act
	
	// Assert
	EXPECT_EQ(attribute1, attribute2);
}

/* 
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
*/

TEST(XmlAttribute, PrintsAsXml)
{
	// Arrange
	string expected("attrx=99");
	XmlAttribute attribute{"attrx", "99"};
	ostringstream stream;
	stream << XmlStreamModifiers::XmlFormat;
	
	// Act
	stream << attribute;
	
	// Assert
	EXPECT_EQ(expected, stream.str());
}

TEST(XmlAttribute, PrintsAsVerbose)
{
	// Arrange
	string expected("attrx:99");
	XmlAttribute attribute{"attrx", "99"};
	ostringstream stream;
	stream << XmlStreamModifiers::VerboseFormat;
	
	// Act
	stream << attribute;
	
	// Assert
	EXPECT_EQ(expected, stream.str());
}

