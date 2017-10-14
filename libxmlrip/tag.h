#ifndef TAG_H
#define TAG_H

#include <string>

class Tag
{
public:
	Tag(std::string tagName, bool isOpeningTag, bool isClosingTag);

public:
	bool IsOpeningTag() const;
	bool IsClosingTag() const;
	std::string GetTagName() const;

	bool operator==(const Tag& t1) const;

private:
	std::string m_tagName;
	bool m_isOpeningTag;
	bool m_isClosingTag;
};

std::ostream& operator<<(std::ostream& os, const Tag& tag);

#endif