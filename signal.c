#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

static void sig_usr(int);
int main(void){
    
    if(signal(SIGUSR1,sig_usr)==SIG_ERR){
        perror("signal signaluser1");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR2,SIG_DFL)==SIG_ERR){
        perror("signal signaluser2");
        exit(EXIT_FAILURE);
    }

    for(; ;)
    pause();

}

static void sig_usr(int signum){
    if(signum == SIGUSR1){
        printf("recevied SIGUSR1\n");
    }
    else if(signum == SIGUSR2){
        printf("recevied SIGUSER2\n");
    }
    else{
        printf("recevied singnum %d",signum );
    }
}
