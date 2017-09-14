#include "tokeniser.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "Hello world" << std::endl;

	std::unique_ptr<std::istream> inputStream(new std::ifstream("test.xml"));
	//std::unique_ptr<std::istream>& pp(inputStream);
	//std::unique_ptr<std::istream> test(pp);
	Tokeniser tokeniser(std::move(inputStream));
}

