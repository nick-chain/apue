#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
//关于TCP的三次握手
//链接断开需要四次挥手
int main(void){
    
    //1.创建套接字
    int sofd = socket(AF_INET,SOCK_STREAM,0);
    if(sofd==-1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("create socket success!\n");

    //2.绑定本地IP和端口号
    struct sockaddr_in seraddr;
    int bin;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(7777);
    seraddr.sin_addr.s_addr = inet_addr("192.168.4.129");
    bin = bind(sofd,(const struct sockaddr*)&seraddr,sizeof(seraddr));
    if(bin ==-1){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind success!\n");

    //3.监听套接字
    if(listen(sofd,5)==-1){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("listen success!\n");

    //4.阻塞等待客户机的请求，成功生成通信套接字
    int conntfd = accept(sofd,NULL,NULL);
    if(conntfd==-1){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("accept success!\n");
    
    //5.读写数据，即进行相关操作

    char buf[4096];
    int ret;
    while(1){
        if((ret=read(conntfd,buf,sizeof(buf)))<0){
            perror("read");
            exit(EXIT_FAILURE);
            break;
        }
        else if(0==ret){
            printf("client has closed!\n");
            break;
        }
        else{
            printf("Client:%s",buf);
        }
    }

    close(conntfd);
    close(sofd);

    exit(EXIT_SUCCESS);
}
