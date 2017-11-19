#ifndef INLINEBUFFER_H
#define INLINEBUFFER_H

#include <algorithm>
#include <istream>
#include <memory>

class InlineBuffer
{
public:
	InlineBuffer(std::unique_ptr<std::istream> stream, size_t bufferSize);
	~InlineBuffer();

public:
	inline char peek()
	{
		if (m_pDataNext == m_pDataEnd)
			Fill();

		if ((m_pDataNext == m_pDataEnd) && m_stream->eof())
		{
			m_eof = true;
			return EOF;
		}
				
		return *m_pDataNext;
	}

	inline void get(char& ch)
	{
		if (m_pDataNext == m_pDataEnd)
			Fill();

		if ((m_pDataNext == m_pDataEnd) && m_stream->eof())
		{
			m_eof = true;
			ch = EOF;
			return;
		}

		ch = *m_pDataNext++;
	}

	inline void get(std::streambuf& sb, char delim)
	{
		if (eof())
			return;
		do
		{
			if (m_pDataNext == m_pDataEnd)
				Fill();

			if ((m_pDataNext == m_pDataEnd) && m_stream->eof())
			{
				m_eof = true;
			}
			else
			{
				auto delimPos = std::find(m_pDataNext, m_pDataEnd, delim);
				sb.sputn(m_pDataNext, delimPos - m_pDataNext);

				m_pDataNext = delimPos;
			}
		} while ((m_pDataNext == m_pDataEnd) && !eof());

	}
	
	inline bool eof()
	{
		return m_eof;
	}

private:
	std::unique_ptr<std::istream> m_stream;
	const size_t m_bufferSize;
	char* m_pBuffer;
	char* m_pDataEnd;
	char* m_pDataNext;
	bool m_eof;

	void Fill();

	InlineBuffer(const InlineBuffer& src) = delete;
	InlineBuffer operator=(const InlineBuffer& src) = delete;
	
};

#endif
