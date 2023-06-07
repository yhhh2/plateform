#include "_public.h"
CLogFile logfile(10);
int main(int argc ,char *argv[])
{
    
      if(argc!=4)
      {
            cout<<"Using:./crtsurfdata1 inifile outpathfile logfile"<<endl;
         cout<<"Example:/project/idc1/bin/crtsurfdata1 /project/idc1/ini/stcode.ini /tmp/surfdata /log/idc/crtsurfdata1.log\n\n";
            return -1;
      }
    if(logfile.Open(argv[3])==false)
    {
    cout<<"logfile.open("<<argv[3]<<") failed"<<endl;
    return -1;
    }
     logfile.Write("crtsurfdata1 开始运行 \n");
    for(int i =0;i<10000000;i++){
 logfile.Write("crtsurfdata1第%010d条日志\n",i);            
    }
    //业务逻辑
    logfile.Write("crtsurfdata1 运行结束 \n"); 

    return 0;
}

