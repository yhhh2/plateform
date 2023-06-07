#include "_public.h"
#include<vector>
CLogFile logfile(10);//日志系统对象10mb

struct st_stcode
{
    char provanme[31];//省
    char obtid[11];//站号
    char obtname[31];//站名
    double lat;//纬度
    double lon;//经度
    double height;//海拔高度
};
vector<struct st_stcode> vstcode;

 bool LoadSTCode(const char *inifile); 
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
    //业务逻辑
    //把站点参数文件加载到vstcode容器
    if(LoadSTCode(argv[1])==false) return -1;
    logfile.Write("crtsurfdata1 运行结束 \n"); 

    return 0;
}

//把站点参数文件加载到vstcode容器
bool LoadSTCode(const char *inifile)
{
    CFile File;

    //打开站点参数文件
    if(File.Open(inifile,"r")==false)
    {
    logfile.Write("File.Open(%s) failed\n",inifile);return -1;
    }
    char strBuffer[301];
    CCmdStr CmdStr;
    struct st_stcode stcode;
    while(true)
    {
    //从站点参数文件读取一行，如果读完，跳出循环
    if(File.Fgets(strBuffer,300,true)==false)break;
    //logfile.Write("=%s=\n",strBuffer);
    //拆分字符串  要拆分的字符串，拆分根据，是否删除前后空格
    CmdStr.SplitToCmd(strBuffer,",",true);
    //删除无效行
    if(CmdStr.CmdCount()!=6) continue;

    //把站点参数的每一个数据保存到站点参数结构体中
    CmdStr.GetValue(0,stcode.provanme,30);
    CmdStr.GetValue(1,stcode.obtid,30);
    CmdStr.GetValue(2,stcode.obtname,30);
    CmdStr.GetValue(3,&stcode.lat);
    CmdStr.GetValue(4,&stcode.lon);
    CmdStr.GetValue(5,&stcode.height);
    
    vstcode.push_back(stcode);
    }

    for(auto a:vstcode){
        logfile.Write("省=%s站号=%s站名=%s纬度=%.2f经度=%.2f海拔高度=%.2f\n",a.provanme,a.obtid,a.obtname,a.lat,a.lon,a.height);
        
    }
return true;
}
