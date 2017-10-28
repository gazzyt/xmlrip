#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop


#include "xmlelement.h"

using namespace std;


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

TEST(XmlElement, CreatesCorrectElementFromNameAndAttributes) {
	// Arrange
	string tagText{"aa att=3"};
	
	// Act
	XmlElement element = XmlElement::FromText(tagText, true, true);
	
	// Assert
	EXPECT_TRUE(element.IsOpeningTag());
	EXPECT_TRUE(element.IsClosingTag());
	EXPECT_EQ("aa", element.GetTagName());
	EXPECT_EQ(" att=3", element.GetAttributeText());
}
