#include <cassert>
#include <iostream>

#include "xmlelementreader.h"

using namespace std;

XmlElementReader::XmlElementReader(unique_ptr<istream> stream)
:	m_stream(move(stream))
{
}


XmlElement XmlElementReader::GetNextElement()
{
    string tagName;
    char c;
    
    m_stream->ignore(1, '<');
	
    
    if (m_stream->peek() == '?')
    {
		m_stream->get(c);
		return ReadDeclaration();
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