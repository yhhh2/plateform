#include "_public.h"
#include<vector>
CLogFile logfile(10);//日志系统对象10mb
//存放全国气象站点数据
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
//存放全国气象站点分钟观测数据
struct st_surfdata                                                                   
  {                                                                                    
    char obtid[11];      // 站点代码。                                                 
    char ddatetime[21];  // 数据时间：格式yyyymmddhh24miss                             
    int  t;              // 气温：单位，0.1摄氏度。                                    
    int  p;              // 气压：0.1百帕。                                            
    int  u;              // 相对湿度，0-100之间的值。                                  
    int  wd;             // 风向，0-360之间的值。                                      
    int  wf;             // 风速：单位0.1m/s                                           
    int  r;              // 降雨量：0.1mm。                                            
    int  vis;            // 能见度：0.1米。                                            
  };
vector<struct st_surfdata> vsurfdata;



 bool LoadSTCode(const char *inifile);
 void CrtSurfData();
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
    //模拟全国生成气象战点分钟观测数据，存放在vsurfdata容器
    CrtSurfData();
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
//模拟生成全国气象战点分钟观测数据，存放在vsurfdata容器中
 void CrtSurfData()
{   
    //随机种子
    srand(time(0));
    //获取当前时间，当作观测时间
    char strdatetime[21];
    memset(strdatetime,0,sizeof(strdatetime));
    LocalTime(strdatetime,"yyyymmddhh24miss");
    
    //遍历气象站电参数的vscode容器
    struct st_surfdata stsurfdata;
    for(int i=0;i<vstcode.size();i++)
    {
        memset(&stsurfdata,0,sizeof(struct st_surfdata));
        //用随机数填充分钟观测数据的结构体
  strncpy(stsurfdata.obtid,vstcode[i].obtid,10) ;      // 站点代码。                                                 
   strncpy(stsurfdata.ddatetime,strdatetime,14);  // 数据时间：格式yyyymmddhh24miss                             
      stsurfdata.t = rand()%351;              // 气温：单位，0.1摄氏度。                                    
    stsurfdata.p = rand()%256+10000;              // 气压：0.1百帕。                                            
       stsurfdata.u=rand()%100+1;              // 相对湿度，0-100之间的值。                                  
       stsurfdata.wd=rand()%360;             // 风向，0-360之间的值。                                      
       stsurfdata.wf=rand()%150;             // 风速：单位0.1m/s                                           
       stsurfdata.r=rand()%16;              // 降雨量：0.1mm。                                            
       stsurfdata.vis=rand()%5001+100000;            // 能见度：0.1米。         

        //把观测数据的结构体放入vsurfdata容器
        vsurfdata.push_back(stsurfdata);
    
    }



}
