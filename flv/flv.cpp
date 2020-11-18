#include "flv.h"
#include <cstdlib>
#include <cstring>

size_t FlvHeader::SIZE = 9;
size_t FlvTagHeader::SIZE = 15;

bool FlvHeader::Decode(const std::string& from)
{
    if(from.size() < FlvHeader::SIZE)
    {
        return false;
    }
    memcpy((void*)mark,(void*)from.data(),3);
    memcpy((void*)&version,(void*)(from.data()+3),1);
    memcpy((void*)&flag,(void*)(from.data()+4),1);
    memcpy((void*)reserve,(void*)(from.data()+5),4);
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
    memcpy(&pre_tag_len,(void*)from.data(),4);
    memcpy(&type,(void*)(from.data()+4),1);
    memcpy(content,(void*)(from.data()+5),3);
    memcpy(time,(void*)(from.data()+8),3);
    memcpy(&timeext,(void*)(from.data()+11),1);
    memcpy(streamid,(void*)(from.data()+12),3);
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
