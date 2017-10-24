#include "tagreader.h"
#include <iostream>

using namespace std;

TagReader::TagReader(unique_ptr<istream> stream)
:	m_stream(move(stream))
{
}


Tag TagReader::GetNextTag()
{
    string tagName;
    char c;
    bool startTag = false;
    bool endTag = false;
    
    m_stream->ignore(1, '<');
    
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
            return Tag::FromText("EOF", false, false);
            
        if (c == '/')
        {
            endTag = true;
        }
        else if (c == '>')
        {
            return Tag::FromText(tagName, startTag, endTag);
        }
        else
        {
            tagName += c;
        }
    };
    
    //return Tag("dummy",true, true);
}

