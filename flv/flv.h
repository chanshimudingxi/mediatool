#ifndef FLV_H_
#define FLV_H_

#include <string>
#include <stdint.h>

/*************************************************
 * ----------------------------------------------
 * Flv Header|Flv Body                           |
 * ----------|-----------------------------------|
 * Flv Header|Flv Tag1| Flv Tag2| ......|Flv Tagn|
 * -----------------------------------------------
 ************************************************/

#pragma pack(1)

struct FlvHeader
{
    uint8_t mark[3];//文件格式标识（FLV 0x46 0x4C 0x56）
    uint8_t version;//版本（0x01）
    uint8_t flag;//前5个bit是保留的必须是0,第6个bit音频类型标志（TypeFlagsAudio），第7个bit也是保留的必须是0，第8个bit视频类型标志（TypeFlagsVideo）
    uint8_t reserve[4];//保留,数据为0x00000009

    bool Decode(char* from, int size);
    bool Encode(std::string*);
    static size_t SIZE;
};

struct FlvTagHeader
{
    uint32_t pre_tag_len;//前一个tag长度
    uint8_t type;//tag类型
    uint8_t content[3]; //tag内容大小
    uint8_t time[3];//时间戳（毫秒）（第1个tag的时候总是为0,如果是脚本tag就是0）
    uint8_t timeext;//时间戳扩展,本字节作为时间戳的最高位
    uint8_t streamid[3];//streamID

    bool Decode(char* from, int size);
    bool Encode(std::string*);
    static size_t SIZE;
};


struct FlvTag
{
    FlvTagHeader header;
    std::string data;

    bool Decode(char* from, int size);
    bool Encode(std::string*);
    size_t Size();
};
#pragma pack()
#endif