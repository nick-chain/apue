#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void func(int signum){
    if(signum == SIGINT){
        printf("----------------\n");
    }
    if(signum == SIGTSTP){
        printf("*******************\n");
    }
}

int main(void){
    int i=0;

    //忽略该信号
   // signal(SIGTSTP,SIG_IGN);
    //signal(SIGINT,func);
    while(1){
        while(i==10){
            signal(SIGTSTP,func);
         //   signal(SIGINT,SIG_DFL);
        }
        i++;
        signal(SIGTSTP,SIG_IGN);
        printf("How are you nick\n");
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}


