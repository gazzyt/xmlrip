#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "xmlpredicate.h"

using namespace std;


TEST(XmlPredicate, IsMatchReturnsTrueWhenOpeningTagNamesMatch) {
    XmlElement testElement("aa", true, false);
    XmlPredicate testPredicate("aa");
    
	EXPECT_TRUE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsTrueWhenOpeningClosingTagNamesMatch) {
    XmlElement testElement("aa", true, true);
    XmlPredicate testPredicate("aa");
    
	EXPECT_TRUE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenClosingTagNamesMatch) {
    XmlElement testElement("aa", false, true);
    XmlPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenOpeningTagNamesDoNotMatch) {
    XmlElement testElement("bb", true, false);
    XmlPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}

TEST(XmlPredicate, IsMatchReturnsFalseWhenOpeningClosingTagNamesDoNotMatch) {
    XmlElement testElement("cc", true, true);
    XmlPredicate testPredicate("aa");
    
	EXPECT_FALSE(testPredicate.IsMatch(testElement));
}
