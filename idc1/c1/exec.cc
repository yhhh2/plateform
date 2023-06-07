#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc,char * argv[])
{   
    //关闭信号和IO
    for(int i =0;i<64;i++)
    {
        signal(i,SIG_IGN); close(i);
    }
    //父进程退出 子进程由1号托管
    if(fork()!=0) exit(0);
    
    //启用SIGCHLD信号，让父进程可以wait子进程退出状态
    signal(SIGCHLD,SIG_DFL);

    char *pargv[argc];
    for(int i =2;i<argc;i++)
        pargv[i-2]=argv[i];
        
    pargv[argc-2]=NULL;
    while(1)
    {    
        if(fork() ==0)
        {
        execv(argv[2],pargv);
        exit(0);    
        }else
        {
            int status;
            wait(&status);
            sleep(atoi(argv[1]));
        }   

    }
    return 0;
}

