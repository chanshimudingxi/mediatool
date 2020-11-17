#ifndef FLV_PARSER_H_
#define FLV_PARSER_H_

#include "flv.h"
#include <string>

class FlvParser
{
public:
    bool parse_file(std::string filename);
public:
    FlvHeader m_flv_header;
    vector<FlvTagHeader> m_flv_tagheader;
};


#endif