#include "flv.h"

bool FlvHeader::Decode(const std::string& from)
{
    if(from.size() < 9)
    {
        return false;
    }
    memcpy(mark,from.data,3);
    memcpy(&version,from.data+3,1);
    memcpy(&flag,from.data+4,1);
    memcpy(reserve,from.data+5,4);
}

bool FlvHeader::Encode(std::string* to)
{
    
}


bool FlvTagHeader::Decode(const std::string& from)
{

}

bool FlvTagHeader::Encode(std::string* to)
{

}

bool FlvTag::Decode(const std::string& from)
{

}

bool FlvTag::Encode(std::string* to)
{

}
