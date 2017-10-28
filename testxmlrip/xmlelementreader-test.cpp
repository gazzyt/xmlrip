#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "xmlelementreader.h"

using namespace std;

static const string simpleXml = "<a></a>";
static const auto simpleXmlElements = {
	XmlElement{"a", true, false}, 
	XmlElement{"a", false, true}
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
