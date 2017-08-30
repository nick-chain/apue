#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>
#include<fcntl.h>
#define myfifo "/home/linux/myfifo"
char buf[128];
//写管道
int main(){
    int n,fd;
 
    //没有文件就创建
    if(mkfifo(MYFIFO,0666)<0){
            perror("fail mkfifo");
            exit(EXIT_FAILURE);
        }
    if((fd = open("./myfifo",O_RDONLY))<0){
        perror("open fail");
        exit(EXIT_FAILURE);
    }

    while(1){
        if((n=read(fd,buf,128))>0){
            printf("%s\n",buf);
        }
        
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
