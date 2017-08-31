#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFSIZE 128
//循环服务器模式，一次只能处理一个客户端请求
//无法处理并发的情况，实际运用中较少
typedef struct sockaddr* Addr;

int main(int argc, char* argv[]){
    struct sockaddr_in seraddr,cliaddr;
    int sockfd,n;
    socklen_t len;
    char buf[BUFFSIZE];
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    printf("create sockfd success!\n");

    //绑定本地主机和端口号
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(7777);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if((bind(sockfd,(Addr)&seraddr,sizeof(seraddr)))<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind success!\n");

    if(listen(sockfd,10)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("listen success!\n");

    len = sizeof(cliaddr);
    int accfd;
    while(1){
        if((accfd=accept(sockfd,(Addr)&cliaddr,&len))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("accept success!\n");
        while(1){
            n = read(accfd,buf,sizeof(buf));
            printf("%d\n",n);
            if(n<0){
                perror("read");
                exit(EXIT_FAILURE);
            }
            else{
                printf("Receive client:%s\n",buf);
            }
            if(strncmp(buf,"quit",4)==0){
                break;
            }
        }
        //此处一定要关闭套接字，不然一直打开会到上限
        close(accfd);
    }

    return 0;
}
