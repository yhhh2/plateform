#include"_public.h"

void EXIT(int sig)
{
    printf("sig=%d\n",sig); exit(0);
}

CPActive PActive; 
int main(int argc,char * argv[])
{
    if(argc!=3){ printf("Using:./test procname timeout\n"); return 0;};

    signal(2,EXIT); signal(15,EXIT);


PActive.AddPInfo(atoi(argv[2]),argv[1]);

while(true)
{
    PActive.UptATime();

    sleep(10);
}

return 0;
}