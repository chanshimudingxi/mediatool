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
    fs.read((char*)&m_flv_header, sizeof(FlvHeader));

    //tag
    while(fs)
    {
        FlvTagHeader flvTagHeader;
        fs.read((char*)&flvTagHeader, sizeof(FlvTagHeader));
        if(fs)
        {
            m_flv_tagheaders.push_back(flvTagHeader);
            uint32_t contentSize = flvTagHeader.GetContentSize();
            char* buffer = new char[contentSize];
            assert(NULL != buffer);
            fs.read(buffer, contentSize);
            if(fs)
            {
                std::cout << "tag body size: " << contentSize
                    <<", time: "<<flvTagHeader.GetTimeMs()
                    <<", streamid: "<<flvTagHeader.GetStreamId()
                    <<std::endl;
            }
            else
            {
                std::cerr << "error: only " << fs.gcount() << " could be read"<<std::endl;
			    break;
            }
        }
		else
		{
			std::cerr << "error: only " << fs.gcount() << " could be read"<<std::endl;
			break;
		}
	}

    fs.close();
    return true;
}
