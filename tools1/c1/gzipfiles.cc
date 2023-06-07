#include <iostream>
#include<_public.h>
using namespace std;
//2 15 signal 
void EXIT(int sig);

int main(int argc,char* argv[])
{
   //帮助文档
   if(argc !=4)
   {
       std::cout<<std::endl<<"using: /project/tools1/bin/gzipfiles pathname matchstr timeout \n";
    return -1;
   }
// 关闭全部信号和io
//CloseIOAndSignal(true);
signal(SIGINT,EXIT); signal(SIGTERM,EXIT);
// 获取文件超时时间点
char strTimeOut[21];
 LocalTime(strTimeOut,"yyyy-mm-dd hh24:mi:ss",0-(int)(atof(argv[3])*24*60*60));
// 打开目录 
CDir Dir;
if(Dir.OpenDir(argv[1],argv[2],10000,true)==false)
{
    cout<<"OpenDir failed\n"; return -1;
}
// 遍历目录文件名

char strCmd[1024];
while(true)
{
    //得到一个文件的信息
    if(Dir.ReadDir()==false)break;
    //cout<<"FullFileName"<<Dir.m_FullFileName<<endl;
    //与超时时间点比较，如果更早，则压缩
    if( (strcmp(Dir.m_ModifyTime,strTimeOut)<0) && (MatchStr(Dir.m_FileName,"*.gz")==false))    
    {
        //gzip
        SNPRINTF(strCmd,sizeof(strCmd),1000,"/usr/bin/gzip -f %s 1>/dev/null 2>/dev/null",Dir.m_FullFileName);
        if(system(strCmd)==0)
            printf("gzip %s ok.\n",Dir.m_FullFileName);
        else
            cout<<"system failed\n";
    }       
}


    return 0;
}

void EXIT(int sig)
{
    std::cout<<"程序退出,sig="<<sig<<std::endl;
}

