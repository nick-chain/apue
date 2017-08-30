#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define BUFFERSIZE 4096

int main(void){
    pid_t pid;
    char buf[BUFFERSIZE] = "this is deamon\n";
    int fd;

    if((pid=fork())<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid>0){
        exit(EXIT_SUCCESS);
    }
    else{
    setsid();//建立当前会话
    //把工作目录改改变到不能删除的目录如根目录
    chdir("/tmp");
    //重新设置文件权限掩码，设置成任何用户都能读用户
    umask(0);
    //关闭文件描述符
    //或取当前进程最多能打开的文件描述符，通通关闭
    int n = getdtablesize();
    int i;
    for(i=0;i<n;i++){
        close(i);
    }

/*    while(1){
        if((execlp("ls","ls","-l","-hl",NULL)) == -1){
            perror("excel");
            exit(-1);
        }
    }*/
    while(1){
        if((fd = open("deamon.log",O_CREAT|O_WRONLY,0600))<0){
            perror("open fail");
            exit(-1);
        }
        write(fd,buf,strlen(buf));
        close(fd);
        sleep(2);
    }
}
    exit(0);
}
