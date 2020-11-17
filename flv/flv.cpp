#include "flv.h"

size_t FlvHeader::SIZE = 9;
size_t FlvTagHeader::SIZE = 15;

bool FlvHeader::Decode(const std::string& from)
{
    if(from.size() < FlvHeader::SIZE)
    {
        return false;
    }
    memcpy(mark,from.data,3);
    memcpy(&version,from.data+3,1);
    memcpy(&flag,from.data+4,1);
    memcpy(reserve,from.data+5,4);
    return true;
}

bool FlvHeader::Encode(std::string* to)
{
    if(NULL == to)
    {
        return false;
    }
    to->append((char*)mark,3);
    to->append((char*)&version,1);
    to->append((char*)&flag,1);
    to->append((char*)reserve,4);
    return true;
}


bool FlvTagHeader::Decode(const std::string& from)
{
    if(from.size() < FlvTagHeader::SIZE)
    {
        return false;
    }
    memcpy(&pre_tag_len,from.data,4);
    memcpy(&type,from.data+4,1);
    memcpy(content,from.data+5,3);
    memcpy(time,from.data+8,3);
    memcpy(&timeext,from.data+11,1);
    memcpy(streamid,from.data+12,3);
    return true;
}

bool FlvTagHeader::Encode(std::string* to)
{
    if(NULL == to)
    {
        return false;
    }
    to->append((char*)&pre_tag_len,4);
    to->append((char*)&type,1);
    to->append((char*)content,3);
    to->append((char*)time,3);
    to->append((char*)&timeext,1);
    to->append((char*)streamid,3);
    return true;
}


bool FlvTag::Decode(const std::string& from)
{
    if(header.Decode(from))
    {
        data = from.substr(FlvTagHeader::SIZE);
        return true;
    }
    else
    {
        return false;
    }
}

bool FlvTag::Encode(std::string* to)
{
    if(header.Encode(to))
    {
        to->append(data);
    }
}

size_t FlvHeader::Size()
{
    return header.Size() + data.size();
}