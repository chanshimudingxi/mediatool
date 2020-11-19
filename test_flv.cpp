#include "flv/flvparser.h"
#include <iostream>

using namespace std;

int main()
{
    FlvParser  flvparser;
    flvparser.parse_file("test.flv");
    cout<<"file_header:"<<endl
        <<"    mark:"<<flvparser.m_flv_header.mark[0]<<flvparser.m_flv_header.mark[1] <<flvparser.m_flv_header.mark[2]<<endl
        <<"    version:"<<hex<<(uint16_t)flvparser.m_flv_header.version<<endl
        <<"    flag:"<<hex<<(uint16_t)flvparser.m_flv_header.flag<<endl;

    for(int i=0; i<flvparser.m_flv_tagheaders.size(); ++i)
    {
        FlvTagHeader& tag_header = flvparser.m_flv_tagheaders[i];
        cout<<"tag_header:"<<endl
            <<"    len:"<<dec<<tag_header.pre_tag_len<<endl
            <<"    type:"<<hex<<(uint16_t)tag_header.type<<endl
            <<"    content:"<<dec<<tag_header.GetContentSize()<<endl
            <<"    time:"<<dec<<tag_header.GetTimeMs()<<endl
            <<"    timeext:"<<(uint16_t)tag_header.timeext<<endl
            <<"    streamid:"<<dec<<tag_header.GetStreamId()<<endl;
    }
    return 0;
}