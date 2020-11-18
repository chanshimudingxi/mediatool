#include "flv/flvparser.h"
#include <iostream>

using namespace std;

int main()
{
    FlvParser  flvparser;
    flvparser.parse_file("test.flv");
    cout<<"file_header:"<<endl
        <<"    flag:"<<flvparser.m_flv_header.flag<<endl
        <<"    mark:"<<flvparser.m_flv_header.mark<<endl
        <<"    version:"<<flvparser.m_flv_header.version<<endl;
    for(int i=0; i<flvparser.m_flv_tagheader.size(); ++i)
    {
        FlvTagHeader& tag_header = flvparser.m_flv_tagheader[i];
        cout<<"tag_header:"<<endl
            <<"    type:"<<tag_header.type<<endl
            <<"    streamid:"<<tag_header.streamid<<endl
            <<"    len:"<<tag_header.pre_tag_len<<endl
            <<"    time:"<<tag_header.time<<endl
            <<"    timeext:"<<tag_header.timeext<<endl;
    }
    return 0;
}