#include <istream>
#include <memory>

	enum class token {token_lt, token_gt};

class Tokeniser
{
public:
	Tokeniser(std::unique_ptr<std::istream> stream);


public:
	token GetNextToken();

private:
	std::unique_ptr<std::istream> m_stream;

};

