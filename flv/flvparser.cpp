#include <string>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "flvparser.h"

using std::ifstream;
using std::string;

bool FlvParser::parse_file(std::string filename)
{
    ifstream fs;
    fs.open(filename.c_str(),ifstream::binary|ifstream::in);

    char * file_head_buffer = new char [FlvHeader::SIZE];
    assert(NULL != file_head_buffer);
    fs.read(file_head_buffer, FlvHeader::SIZE);
    string str_file_head(file_head_buffer,FlvHeader::SIZE);
    delete [] file_head_buffer;

    if(!m_flv_header.Decode(str_file_head))
    {
		std::cerr<<"file header decode fail"<<std::endl;
        fs.close();
        return false;
    }

    //tag
    while(fs)
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
			std::cerr<<"tag header decode fail"<<std::endl;
            break;
        }
        m_flv_tagheader.push_back(flvtag.header);

        //body
        uint32_t body_size = 0;
        memcpy(&body_size, flvtag.header.content, 3);
        char* tag_body_buffer = new char[body_size];
        assert(NULL != tag_body_buffer);
		std::cout<<"tag body size: "<<body_size<<std::endl;
		fs.read(tag_body_buffer, body_size);

		if (fs)
		{
			string str_tag_body(tag_body_buffer, body_size);
			delete [] tag_head_buffer;
			flvtag.data = str_tag_body;
		}
		else
		{
			delete [] tag_head_buffer;
			std::cerr << "error: only " << fs.gcount() << " could be read"<<std::endl;
			break;
		}
	}

    fs.close();
    return true;
}
