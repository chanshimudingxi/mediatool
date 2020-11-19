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
//9个字节
struct FlvHeader
{
    uint8_t mark[3];//文件格式标识（FLV 0x46 0x4C 0x56）
    uint8_t version;//版本（0x01）
    uint8_t flag;//前5个bit是保留的必须是0,第6个bit音频类型标志（TypeFlagsAudio），第7个bit也是保留的必须是0，第8个bit视频类型标志（TypeFlagsVideo）
    uint8_t reserve[4];//保留,数据为0x00000009
};

//15个字节
struct FlvTagHeader
{
    uint32_t pre_tag_len;//前一个tag长度
    uint8_t type;//tag类型
    uint8_t content[3]; //tag内容大小
    uint8_t time[3];//时间戳（毫秒）（第1个tag的时候总是为0,如果是脚本tag就是0）
    uint8_t timeext;//时间戳扩展,本字节作为时间戳的最高位
    uint8_t streamid[3];//streamID
    inline uint32_t GetContentSize()
    {
        uint32_t res= (uint32_t)content[0];
        res = res <<8 | content[1];
        res = res <<8 | content[2];
        return res;
    }

    inline uint32_t GetTimeMs()
    {
        uint32_t res= (uint32_t)time[0];
        res = res <<8 | time[1];
        res = res <<8 | time[2];
        return res;
    }

    inline uint32_t GetStreamId()
    {
        uint32_t res= (uint32_t)streamid[0];
        res = res <<8 | streamid[1];
        res = res <<8 | streamid[2];
        return res;
    }
};
#pragma pack()
#endif