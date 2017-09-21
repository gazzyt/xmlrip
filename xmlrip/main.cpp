#include "tokeniser.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "Hello world" << std::endl;

	std::unique_ptr<std::ifstream> inputStream(new std::ifstream("test.xml"));
	if (!inputStream->is_open())
	{
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	Tokeniser tokeniser(std::move(inputStream));

	Token t = tokeniser.GetNextToken();
	while (t.GetType() != Token::Type::eof)
	{
		std::cout << "token: " << t.GetName() << std::endl;
		t = tokeniser.GetNextToken();
	};
}

