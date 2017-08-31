#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
	//1.创建套接字
    int sofd = socket(AF_INET,SOCK_STREAM,0);
    if(sofd==-1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("create socket success!\n");

    /*2. 主动向服务器发起连接请求*/
    int connt;
    struct sockaddr_in cliaddr;
    memset(&cliaddr,0,sizeof(cliaddr));
    int bin;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(8000);
    cliaddr.sin_addr.s_addr = inet_addr("192.168.4.157");
    connt = connect(sofd,(const struct sockaddr*)&cliaddr,sizeof(cliaddr));
    if(connt==-1){
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("connect the server success!\n");
	/*3. 数据的收发*/
    char buf[4096];
    int ret;
    while(1){
        while((ret=read(STDIN_FILENO,buf,4096))>0){
            if(ret<0){
                perror("read");
                exit(EXIT_FAILURE);
                break;
            }
            if(write(sofd,buf,ret)<0){
                perror("send");
                exit(EXIT_FAILURE);
            }
        }
    }
	/*4. 关闭套接字*/
   // close(connt);
    close(sofd);

    exit(EXIT_SUCCESS);

}
 
