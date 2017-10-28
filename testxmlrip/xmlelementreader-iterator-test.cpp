#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "xmlelementreader-iterator.h"

using namespace std;

static const string simpleXml = "<a></a>";
static const vector<XmlElement> simpleXmlElements = {
	XmlElement{XmlElement::Type::tag, "a", true, false}, 
	XmlElement{XmlElement::Type::tag, "a", false, true}
};


TEST(XmlElementReader_iterator, CreatesCorrectElementsForSimpleXml) {
	auto xmlStream = make_unique<istringstream>(simpleXml);
	XmlElementReader elementReader{move(xmlStream)};
	XmlElementReader_iterator beginIter{elementReader};
	XmlElementReader_iterator endIter{};
	
	vector<XmlElement> actualElements{};
	
	copy(beginIter, endIter, back_inserter(actualElements));
	
	ASSERT_EQ(simpleXmlElements.size(), actualElements.size());
	EXPECT_TRUE(equal(begin(simpleXmlElements), end(simpleXmlElements), begin(actualElements)));
}

TEST(XmlElementReader_iterator, PreIncrementReturnNewIterator) {
	// Arrange
	auto xmlStream = make_unique<istringstream>(simpleXml);
	XmlElementReader elementReader{move(xmlStream)};
	XmlElementReader_iterator beginIter{elementReader};
	XmlElementReader_iterator endIter{};
	
	// Act
	XmlElementReader_iterator newIter = ++beginIter;
	
	// Assert
	EXPECT_EQ(simpleXmlElements[1], *beginIter);
	EXPECT_EQ(simpleXmlElements[1], *newIter);
}

TEST(XmlElementReader_iterator, PostIncrementReturnsOldIterator) {
	// Arrange
	auto xmlStream = make_unique<istringstream>(simpleXml);
	XmlElementReader elementReader{move(xmlStream)};
	XmlElementReader_iterator beginIter{elementReader};
	XmlElementReader_iterator endIter{};
	
	// Act
	XmlElementReader_iterator oldIter = beginIter++;
	
	// Assert
	EXPECT_EQ(simpleXmlElements[1], *beginIter);
	EXPECT_EQ(simpleXmlElements[0], *oldIter);
}
