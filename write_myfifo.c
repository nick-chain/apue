#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>
#include<fcntl.h>
char buf[128];
//写管道
int main(int argc, char* argv[]){
    
    int n,fd0,fd,fd1;

    if(argc!=3){
        perror("too few argument");
        exit(EXIT_FAILURE);
    }
    if(access("myfifo",F_OK)==-1){
        //若管道文件不存在
        if(mkfifo("myfifo",0666)<0){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    if((fd0=open("myfifo",O_RDWR))<0){
        perror("open fd");
        exit(EXIT_FAILURE);
    }

    if((fd=open(argv[1],O_RDONLY,0666))<0){
        perror("open fd");
        exit(EXIT_FAILURE);
    }

    if((fd1=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666))<0){
        perror("open fd");
        exit(EXIT_FAILURE);
    }
    

    while((n=read(fd,buf,128))>0){
        if(write(fd0,buf,n)!=n){
            perror("write");
            exit(EXIT_FAILURE);
            }
    }
        
     while((n=read(fd0,buf,128))>0){
        if(write(fd1,buf,n)!=n){
            perror("write");
            exit(EXIT_FAILURE);
            }
    }   

    close(fd0);
    close(fd);
    close(fd1);
    exit(EXIT_SUCCESS);
    
}
