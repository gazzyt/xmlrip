#ifndef TAGREADER_H
#define TAGREADER_H

#include "tag.h"
#include <istream>
#include <memory>

class TagReader
{
public:
	TagReader(std::unique_ptr<std::istream> stream);


public:
	Tag GetNextTag();

private:
	std::unique_ptr<std::istream> m_stream;

	TagReader(const TagReader& src) = delete;
	TagReader operator=(const TagReader& src) = delete;
	
};

#endif
