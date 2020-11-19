#ifndef FLV_PARSER_H_
#define FLV_PARSER_H_

#include "flv.h"
#include <string>
#include <vector>

class FlvParser
{
public:
    FlvParser(){}
    ~FlvParser(){}
    bool parse_file(std::string filename);
public:
    FlvHeader m_flv_header;
    std::vector<FlvTagHeader> m_flv_tagheaders;
};


#endif