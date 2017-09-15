#include "tokeniser.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "Hello world" << std::endl;

	std::unique_ptr<std::istream> inputStream(new std::ifstream("test.xml"));
	Tokeniser tokeniser(std::move(inputStream));

	Token t = tokeniser.GetNextToken();
}

