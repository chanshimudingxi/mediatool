#include "flv.h"
#include <cstdlib>
#include <cstring>

size_t FlvHeader::SIZE = 9;
size_t FlvTagHeader::SIZE = 15;

bool FlvHeader::Decode(char* from, int size)
{
    if(size < FlvHeader::SIZE || from == NULL)
    {
        return false;
    }
    char* cur = from;
    memcpy((void*)mark,(void*)cur,3);
    cur += 3;
    memcpy((void*)&version,(void*)cur,1);
    cur += 1;
    memcpy((void*)&flag,(void*)cur,1);
    cur += 1;
    memcpy((void*)reserve,(void*)cur,4);
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


bool FlvTagHeader::Decode(char* from, int size)
{
    if(size < FlvTagHeader::SIZE || from == NULL)
    {
        return false;
    }
    char* cur = from;
    memcpy(&pre_tag_len,(void*)cur,4);
    cur += 4;
    memcpy(&type,(void*)cur,1);
    cur += 1;
    memcpy(content,(void*)cur,3);
    cur += 3;
    memcpy(time,(void*)cur,3);
    cur += 3;
    memcpy(&timeext,(void*)cur,1);
    cur += 1;
    memcpy(streamid,(void*)cur,3);
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


bool FlvTag::Decode(char* from, int size)
{
    if(header.Decode(from,size))
    {
        data.append(from+FlvTagHeader::SIZE,size);
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
