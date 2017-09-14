#include <string>

class Token
{
public:
	Token(std::string tagName, bool isOpeningTag, bool isClosingTag);

public:
	bool IsOpeningTag() const;
	bool IsClosingTag() const;
	std::string GetTagName() const;

private:
	std::string m_tagName;
	bool m_isOpeningTag;
	bool m_isClosingTag;
};

