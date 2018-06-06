#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "recordingprinter.h"
#include "libxmlxpathprocessor.h"
#include "libxmlattributecollection.h"
#include "xmlexpression.h"
#include "exception/xpathexception.h"
#include "customprinters.h"

using namespace std;

void RunE2ETest(const string& xmlText, const string& xpathText, const vector<RecordingPrinterItem>& expected) 
{
	// Arrange
	auto expr = XmlExpression::FromText(xpathText);
	RecordingPrinter printer;
	
	// Act
	LibXmlXPathProcessor<RecordingPrinter>::Run(xmlText.c_str(), xmlText.length(), move(expr), printer);
    
	// Assert
	EXPECT_EQ(expected, printer.GetRecordedItems());
}

TEST(XPath, TwoLevelXPathFromRoot) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "bb"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};
	
	// Act
	RunE2ETest("<aa><bb></bb></aa>", "/aa/bb", expected);
}

TEST(XPath, OneLevelXPathFromRoot) {
	// Arrange
	vector<RecordingPrinterItem> expected;
	
	// Act
	RunE2ETest("<aa><bb></bb></aa>", "/bb", expected);
}

TEST(XPath, OneLevelXPathAnyDepth) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "bb"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};
	
	// Act
	RunE2ETest("<aa><bb></bb></aa>", "//bb", expected);
}

TEST(XPath, TwoLevelXPathAnyDepth) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "bb"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};

	// Act
	RunE2ETest("<xx><aa><yy><bb></bb></yy></aa></xx>", "//aa//bb", expected);
}

TEST(XPath, TwoLevelXPathAnyDepthConsecutive) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "bb"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};

	// Act
	RunE2ETest("<xx><aa><yy><bb></bb></yy><bb/></aa></xx>", "//aa/bb", expected);
}

TEST(XPath, ThreeLevelXPathFromRootMultipleMatches) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "cc"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "cc"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "cc"},
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "dd"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};

	// Act
	RunE2ETest("<aa><bb><cc/><cc/></bb><bb/><bb><cc><dd/></cc></bb></aa>", "/aa/bb/cc", expected);
}

TEST(XPath, TwoLevelXPathWithAttribute) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "bb", vector<pair<string, string>>{{"a", "1"}}},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "bb", vector<pair<string, string>>{{"a", "1"},{"b", "2"}}},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};

	// Act
	RunE2ETest("<aa><bb a='1'></bb><bb a='1' b='2'/><bb a='2'></bb></aa>", "/aa/bb[@a='1']", expected);
}

TEST(XPath, SimpleXPathWithText) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "aa"},
		RecordingPrinterItem{RecordingPrinterItem::TEXT, "Here is the text"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};

	// Act
	RunE2ETest("<aa>Here is the text</aa>", "/aa", expected);
}

TEST(XPath, SimpleXPathWithCData) {
	// Arrange
	vector<RecordingPrinterItem> expected = {
		RecordingPrinterItem{RecordingPrinterItem::START_ELEMENT, "aa"},
		RecordingPrinterItem{RecordingPrinterItem::CDATA, "Here is the cdata"},
		RecordingPrinterItem{RecordingPrinterItem::END_ELEMENT, ""},
	};

	// Act
	RunE2ETest("<aa><![CDATA[Here is the cdata]]></aa>", "/aa", expected);
}
