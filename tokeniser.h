#ifndef TOKENISER_H
#define TOKENISER_H

#include "token.h"
#include <istream>
#include <memory>


class Tokeniser
{
public:
	Tokeniser(std::unique_ptr<std::istream> stream);


public:
	Token GetNextToken();

private:
	std::unique_ptr<std::istream> m_stream;

	Tokeniser(const Tokeniser& src) = delete;
	Tokeniser operator=(const Tokeniser& src) = delete;
};

#endif
