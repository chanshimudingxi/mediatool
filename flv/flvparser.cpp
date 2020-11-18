#include <string>
#include <fstream>
#include <cassert>
#include "flvparser.h"

using std::fstream;
using std::string;

bool FlvParser::parse_file(std::string filename)
{
    fstream fs;
    fs.open(filename,fstream::binary);

    char * file_head_buffer = new char [FlvHeader::SIZE];
    assert(NULL != file_head_buffer);
    fs.read(file_head_buffer, FlvHeader::SIZE);
    string str_file_head(file_head_buffer,FlvHeader::SIZE);
    delete [] file_head_buffer;

    if(!m_flv_header.Decode(str_file_head))
    {
        fs.close();
        return false;
    }

    //tag
    while(fs.eof())
    {
        FlvTag flvtag;

        //head
        char * tag_head_buffer = new char [FlvTagHeader::SIZE];
        assert(NULL != tag_head_buffer);
        fs.read(tag_head_buffer, FlvTagHeader::SIZE);
        string str_tag_head(tag_head_buffer, FlvTagHeader::SIZE);
        delete [] tag_head_buffer;
        if(!flvtag.header.Decode(str_tag_head))
        {
            break;
        }
        m_flv_tagheader.push_back(flvtag.header);

        //body
        uint32_t body_size = 0;
        memcpy(&body_size, flvtag.header.content, 3);
        char* tag_body_buffer = new char[body_size];
        assert(NULL != tag_body_buffer);
        fs.read(tag_body_buffer, body_size);
        string str_tag_body(tag_body_buffer, body_size);
        delete [] tag_head_buffer;
        flvtag.data = str_tag_body;
    }

    fs.close();
    return true;
}