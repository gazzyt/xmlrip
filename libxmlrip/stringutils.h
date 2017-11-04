#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <cctype>
#include <string>
#include <algorithm>
#include <vector>

std::vector<std::string> split(const std::string &s, char delim);

inline std::string trim(const std::string& str)
{
	auto wsfront = std::find_if_not(str.begin(), str.end(), [](int ch){return std::isspace(ch);});
	auto wsback = std::find_if_not(str.rbegin(), str.rend(), [](int ch){return std::isspace(ch);}).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

#endif