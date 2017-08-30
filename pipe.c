#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#define MAXLEN 100
char line[MAXLEN];

int main(void){
    int fd[2];
    int n;
    pid_t pid;
    if(pipe(fd)==-1){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    if((pid = fork())<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid>0){
        close(fd[0]);
        if(write(fd[1],"How are you nick\n",17)<0){
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    else{
        close(fd[1]);
        if((n = read(fd[0],line,MAXLEN))<0){
            perror("read");
            exit(EXIT_FAILURE);
        }
        if(write(STDOUT_FILENO,line,n)<0){
            perror("write stdout");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
