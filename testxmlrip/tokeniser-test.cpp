#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include <algorithm>
#include <memory>
#include <sstream>

#include "tokeniser.h"

using namespace std;

static const string simpleXml = "<a></a>";
static const auto simpleXmlTokens = {
	Token{Token::Type::lt}, 
	Token{Token::Type::string, "a"},
	Token{Token::Type::gt},
	Token{Token::Type::lt_slash},
	Token{Token::Type::string, "a"},
	Token{Token::Type::gt},
	Token{Token::Type::eof}
};


TEST(Tokeniser, CreatesCorrectTokensForSimpleXml) {
	int tokenIndex = 0;
	auto xmlStream = make_unique<istringstream>(simpleXml);
	Tokeniser tokeniser{move(xmlStream)};
	
	for_each(begin(simpleXmlTokens), end(simpleXmlTokens), 
		[&] (const Token& t) 
		{
			EXPECT_EQ(t,tokeniser.GetNextToken()) << "Token number " << tokenIndex << " did not have expected value";
			++tokenIndex;
		}
	);
}
