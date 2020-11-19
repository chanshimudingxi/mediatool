#include "flv/flvparser.h"
#include <iostream>

using namespace std;

int main()
{
    FlvParser  flvparser;
    flvparser.parse_file("test.flv");
    cout<<"file_header:"<<endl
        <<"    mark:"<<hex<<flvparser.m_flv_header.mark[0]<<flvparser.m_flv_header.mark[1] <<flvparser.m_flv_header.mark[2]<<endl
        <<"    version:"<<hex<<flvparser.m_flv_header.version<<endl
        <<"    flag:"<<hex<<flvparser.m_flv_header.flag<<endl;

    for(int i=0; i<flvparser.m_flv_tagheader.size(); ++i)
    {
        FlvTagHeader& tag_header = flvparser.m_flv_tagheader[i];
        cout<<"tag_header:"<<endl
            <<"    len:"<<hex<<tag_header.pre_tag_len<<endl
            <<"    type:"<<hex<<tag_header.type<<endl
            <<"    content:"<<tag_header.content[0]<<tag_header.content[1]<<tag_header.content[2]<<endl
            <<"    time:"<<tag_header.time[0]<<tag_header.time[1]<<tag_header.time[2]<<endl
            <<"    timeext:"<<tag_header.timeext<<endl
            <<"    streamid:"<<tag_header.streamid[0]<<tag_header.streamid[1]<<tag_header.streamid[2]<<endl;
    }
    return 0;
}