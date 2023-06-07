 #include"_public.h"

   struct st_pinfo                                             
   {                                                           
       int pid;                                                
       char pname[51];                                         
       int timeout;  //超时时间                                
       time_t atime; //最后一次心跳时间                        
                                                               
  };                                                          
                                                              
  int main(int argc,char *argv[])                             
  {                                                           
          if(argc<2){cout<<"using: ./shm procname\n";}        
                                                              
          //创建、获取共享内存，大小为n*sizeof                
          int m_shmid=0;
          if((m_shmid=shmget(SHMKEYP,MAXNUMP*sizeof(struct st_pinfo),0640|IPC_CREAT))==-1)
          {
            cout<<"shmget failed\n";
          }
            CSEM m_sem;
            m_sem.init(SEMKEYP);

          //bin间共享内存连接到当前进程地址空间                  
            struct st_pinfo * m_shm;
            if((m_shm=(struct st_pinfo*)shmat(m_shmid,0,0))==(void *)-1)
            {
            cout<<"shmat failed\n";
            }
          //创建当前进程心跳信息结构体变量，把本进程的信息填进
            struct st_pinfo stpinfo;
            memset(&stpinfo,0,sizeof(struct st_pinfo));
            stpinfo.pid=getpid();
            STRNCPY(stpinfo.pname,sizeof(stpinfo.pname),argv[1],50);
            stpinfo.timeout=30;
            stpinfo.atime=time(0);

            int m_pos=-1;
            //pid复用问题
             for(int i=0;i<SHMKEYP;i++)
            {
            if(m_shm[i].pid==stpinfo.pid)
            {
             m_pos=i;break;
            }}
            m_sem.P();
          //在共享内存空位置，把当前进程心跳信息存入共享内存中
            if(m_pos==-1){
            for(int i=0;i<SHMKEYP;i++)
             {
            if(m_shm[i].pid==0)
                {
             m_pos=i;break;
                }
             }
            }

            if(m_pos==-1)
            {
                m_sem.V();
            cout<<"shmcpy failed\n"; return -1;
            }
            memcpy(m_shm+m_pos,&stpinfo,sizeof(st_pinfo));
         m_sem.V();

            while(1)                                            
         {                                                   
          //更新共享内存中本进程的心跳时间                    
            m_shm[m_pos].atime=time(0);
             sleep(10);                                      
          }                                                                                                                
          //吧当前进程从共享内存中移除                        
            memset(m_shm+m_pos,0,sizeof(struct st_pinfo));                       
          //把共享内存从档期那进程分离  
            shmdt(m_shm);
  }

