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

    if(!m_flv_header.Decode(file_head_buffer, FlvHeader::SIZE))
    {
		std::cerr<<"file header decode fail"<<std::endl;
        delete [] file_head_buffer;
        fs.close();
        return false;
    }
    delete [] file_head_buffer;


    //tag
    while(fs)
    {
        FlvTag flvtag;

        //head
        char * tag_head_buffer = new char [FlvTagHeader::SIZE];
        assert(NULL != tag_head_buffer);
        fs.read(tag_head_buffer, FlvTagHeader::SIZE);
        if(!flvtag.header.Decode(tag_head_buffer, FlvTagHeader::SIZE))
        {
			std::cerr<<"tag header decode fail"<<std::endl;
            delete [] tag_head_buffer;
            break;
        }
        m_flv_tagheader.push_back(flvtag.header);
        delete [] tag_head_buffer;

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
