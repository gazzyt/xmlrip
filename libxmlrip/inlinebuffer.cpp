#include <cassert>
#include <iostream>
#include <sstream>

#include "inlinebuffer.h"

using namespace std;

InlineBuffer::InlineBuffer(unique_ptr<istream> stream, size_t bufferSize)
:	m_stream(move(stream)),
	m_bufferSize{ bufferSize },
	m_pBuffer{new char[bufferSize]},
	m_pDataEnd{m_pBuffer},
	m_pDataNext{m_pDataEnd}
{
	assert(m_stream);
}

InlineBuffer::~InlineBuffer()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
}

void InlineBuffer::Fill()
{
	assert(m_pDataNext == m_pDataEnd);

	m_stream->read(m_pBuffer, m_bufferSize);

	m_pDataNext = m_pBuffer;

	if (*m_stream)
	{
		// We read everything we asked for
		m_pDataEnd = m_pBuffer + m_bufferSize;
	}
	else
	{
		m_pDataEnd = m_pBuffer + m_stream->gcount();
	}
}
