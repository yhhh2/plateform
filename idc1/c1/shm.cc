#include <iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<cstring>
#include<unistd.h>
struct st_pid
{
    int pid;
    char name[51];

};

int main(int argc,char *argv[])
{
    //共享内存的标志
    int shmid;    
    //获取或者创建内存，键值0x5005
    if((shmid= shmget(0x5005,sizeof(struct st_pid),0664|IPC_CREAT))==-1)
    {
        std::cout<<"shmid(0x5005) failed\n"; return -1;
    }
    
    struct st_pid * stpid=0;
    //把共享内存连接到当前进程的地址空间
    if((stpid= (struct st_pid *)shmat(shmid,0,0))==(void *)-1)
    {
        std::cout<<"shmat failed\n"; return -1;
    }

    std::cout<<"pid="<<stpid->pid<<"name="<<stpid->name<<std::endl;

    //操作共享内存
    stpid->pid=getpid();
    strcpy(stpid->name,argv[1]);

    
    std::cout<<"pid="<<stpid->pid<<"name="<<stpid->name<<std::endl;
    //共享内存从当前进程分离
    shmdt(stpid);
   /* 
    if(shmctl(shmid,IPC_RMID,0)==-1)
    {
    std::cout<<"shmctl failed"<<std::endl;
    return -1;
    }*/

    return 0;
}

