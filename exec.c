#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

/**int execve(const char* path, char *const argv[], char *const envp[]);
path:执行程序的路径
argv:字符指针数组 要执行的参数
envp:指针数组 环境变量 自定义环境变量
*/


int main(void){
    char* argv[] = {"env",NULL};
    char* envp[] = {
        "PATH = /home/nick/prorgam",
        "wenfweflkwfnemer",
        NULL
    };  
    pid_t pid;
    pid = fork();

    if(pid<0){
        perror("fork");
        exit(-1);
    }
    else if(pid>0){
        while(1){
            printf("hello nick\n");
            sleep(1);
        }
    }
    else{
        if(execv("usr/bin/env",argv)<0){
            perror("execve");
            exit(-1);
        }
    }
    exit(0);
}
