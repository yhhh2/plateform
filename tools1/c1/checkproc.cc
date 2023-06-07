#include "_public.h"

// 程序运行的日志。
CLogFile logfile;

int main(int argc,char *argv[])
{
  // 程序的帮助。
  if (argc != 2)
  {
    printf("\n");
    printf("Using:./checkproc logfilename\n");

    printf("Example:/project/tools1/bin/procctl 10 /project/tools1/bin/checkproc /tmp/log/checkproc.log\n\n");

    printf("本程序用于检查后台服务程序是否超时，如果已超时，就终止它。\n");
    printf("注意：\n");
    printf("  1）本程序由procctl启动，运行周期建议为10秒。\n");
    printf("  2）为了避免被普通用户误杀，本程序应该用root用户启动。\n");
    printf("  3）如果要停止本程序，只能用killall -9 终止。\n\n\n");

    return 0;
  }
    //打开日志文件按
    if(logfile.Open(argv[1],"a+")==false)
    {
        printf("logfile.Open failed\n"); return -1;
    }

    //创建或者打开共享内存
    int shmid=0;
    if((shmid=shmget((key_t)SHMKEYP,MAXNUMP*sizeof(struct st_procinfo),0664|IPC_CREAT))==-1)
    {
        logfile.Write("shmget(%x) failed\n",SHMKEYP); return false;
    }

    //将共享内存和当前进程连接
    struct st_procinfo * shm  = (struct st_procinfo *)shmat(shmid,0,0);


    //遍历共享内存
    for(int i=0;i<MAXNUMP;i++)
    {   //空记录
        if(shm[i].pid==0) continue;

        //发送信号0判断进程是否存在
       int ret =  kill(shm[i].pid,0);
       if(ret==-1)
       {
        logfile.Write("进程pid=%d(%s)已经不存在。\n",(shm+i)->pid,(shm+i)->pname);
      memset(shm+i,0,sizeof(struct st_procinfo)); // 从共享内存中删除该记录。
      continue;
       }

       time_t now = time(0);
       if(now-shm[i].atime<shm[i].timeout) continue;
       
      // 如果已超时。
    logfile.Write("进程pid=%d(%s)已经超时。\n",(shm+i)->pid,(shm+i)->pname);

    // 发送信号15，尝试正常终止进程。
    kill(shm[i].pid,15);    

     // 每隔1秒判断一次进程是否存在，累计5秒，一般来说，5秒的时间足够让进程退出。
    for (int jj=0;jj<5;jj++)
    {
      sleep(1);
      ret=kill(shm[i].pid,0);     // 向进程发送信号0，判断它是否还存在。
      if (ret==-1) break;     // 进程已退出。
    } 

    // 如果进程仍存在，就发送信号9，强制终止它。
    if (ret==-1)
      logfile.Write("进程pid=%d(%s)已经正常终止。\n",(shm+i)->pid,(shm+i)->pname);
    else
    {
      kill(shm[i].pid,9);  // 如果进程仍存在，就发送信号9，强制终止它。
      logfile.Write("进程pid=%d(%s)已经强制终止。\n",(shm+i)->pid,(shm+i)->pname);
    }
    
    // 从共享内存中删除已超时进程的心跳记录。
    memset(shm+i,0,sizeof(struct st_procinfo)); // 从共享内存中删除该记录。
       




    }
    


    shmdt(shm);




return 0;
}