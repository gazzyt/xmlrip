#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "libxmlattributecollection.h"
#include "customprinters.h"

using namespace std;


static const xmlChar* testStrings[] = { BAD_CAST "attname1", BAD_CAST "attvalue1", BAD_CAST "attname2", BAD_CAST "attvalue2" };

TEST(LibXmlAttributeCollection, Test1) {
	// Arrange
	LibXmlAttributeCollection coll(testStrings);

	//Act
	// Assert
}

