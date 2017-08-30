#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(void){
    pid_t pid,ret;
    int status;
    if((pid = fork())<0){
        perror("fork");
        exit(-1);
    }
    else if(pid == 0){
        sleep(5);
        exit(-1);
    }
    else{
        do{
            ret = waitpid(pid,&status,0);
            if(ret==0){
                printf("children process not end \n");
                printf("pid = %d status:%d, %d\n",getpid(),WEXITSTATUS(status),ret);
                sleep(1);
            }
        }while(ret==0);
        if(pid==ret){
            printf("child process exit\n");
        }
        else{
            printf("some error\n");
        }
    }
    exit(-1);
}
