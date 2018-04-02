#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "libxmlutils.h"

using namespace std;

TEST(LibXmlUtils, IsSpaceReturnsFalseForStringWithNonSpaceChars) {
	// Arrange
	const char* testString = "some text";
	const xmlChar* testXmlString = reinterpret_cast<const xmlChar *>(testString);
	int len = strlen(testString);
	
	// Act
	bool result = isspace(testXmlString, len);
	
	// Assert
	EXPECT_FALSE(result);
}

TEST(LibXmlUtils, IsSpaceReturnsTrueForNewlineString) {
	// Arrange
	const char* testString = "\n";
	const xmlChar* testXmlString = reinterpret_cast<const xmlChar *>(testString);
	int len = strlen(testString);
	
	// Act
	bool result = isspace(testXmlString, len);
	
	// Assert
	EXPECT_TRUE(result);
}
