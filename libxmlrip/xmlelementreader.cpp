#include <cassert>
#include <iostream>
#include <sstream>

#include "stringutils.h"
#include "xmlelementreader.h"

using namespace std;

XmlElementReader::XmlElementReader(unique_ptr<InlineBuffer> stream)
:	m_stream(move(stream))
{
}


XmlElement XmlElementReader::GetNextElement()
{
    string tagName;
    char c;
    
	if (m_stream->peek() != '<')
	{
		string text = ReadText();
		if (!text.empty())
		{
			return XmlElement{XmlElement::Type::text, text, true, true};
		}
	}

	if (m_stream->eof())
	{
        return XmlElement::FromText("EOF", false, false);
	}
	
	m_stream->get(c);
	assert(c == '<');
	
	if (m_stream->peek() == '?')
	{
		m_stream->get(c);
		return ReadDeclaration();
	}
	else if (m_stream->peek() == '!')
	{
		m_stream->get(c);
		m_stream->get(c);
		assert(c == '-');
		m_stream->get(c);
		assert(c == '-');
		return ReadComment();
	}
	else
	{
		return ReadTag();
	}
}

XmlElement XmlElementReader::ReadTag()
{
    string tagName;
    char c;
    bool startTag = false;
    bool endTag = false;

    if (m_stream->peek() == '/')
    {
		m_stream->get(c);
        endTag = true;
    }
    else
    {
        startTag = true;
    }

    
    while(true)
    {
   		m_stream->get(c);
        
        if (m_stream->eof())
            return XmlElement::FromText("EOF", false, false);
            
        if (c == '/')
        {
            endTag = true;
        }
        else if (c == '>')
        {
            return XmlElement::FromText(tagName, startTag, endTag);
        }
        else
        {
            tagName += c;
        }
    };
}

XmlElement XmlElementReader::ReadDeclaration()
{
    string text;
    char c;

    while(true)
    {
   		m_stream->get(c);
        
        if (m_stream->eof())
            return XmlElement::FromText("EOF", false, false);
            
        if (c == '?')
        {
			m_stream->get(c);
			assert(c == '>');
			return XmlElement{XmlElement::Type::declaration, text, true, true};
        }
        else
        {
            text += c;
        }
    };
}

XmlElement XmlElementReader::ReadComment()
{
    string text;
    char c[3];

    while(true)
    {
   		m_stream->get(c[0]);
        
        if (m_stream->eof())
            return XmlElement::FromText("EOF", false, false);
            
        if (c[0] == '-')
        {
			m_stream->get(c[1]);
			m_stream->get(c[2]);
			if(c[1] == '-' && c[2] == '>')
			{
				return XmlElement{XmlElement::Type::comment, text, true, true};
			}
			else
			{
				text.append(begin(c), begin(c) + 3);
			}
        }
        else
        {
            text += c[0];
        }
    };
}

string XmlElementReader::ReadText()
{
    string text;
	
	m_stream->get(text, '<');
	
	return trim(text);
}
