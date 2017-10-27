#ifndef TAG_H
#define TAG_H

#include <string>

class Tag
{
public:
	Tag(std::string tagName, bool isOpeningTag, bool isClosingTag) noexcept;

public:
	bool IsOpeningTag() const;
	bool IsClosingTag() const;
	std::string GetTagName() const;
	std::string GetAttributeText() const;

	bool operator==(const Tag& t1) const;
	bool IsMatch(const Tag& t1) const;
	
	static Tag FromText(std::string text, bool isOpeningTag, bool isClosingTag);

private:
	Tag(std::string tagName, std::string attributeText, bool isOpeningTag, bool isClosingTag) noexcept;
	
	std::string m_tagName;
	std::string m_attributeText;
	bool m_isOpeningTag;
	bool m_isClosingTag;
};

std::ostream& operator<<(std::ostream& os, const Tag& tag);

#endif