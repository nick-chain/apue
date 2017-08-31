#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#include<arpa/inet.h>
#define BUFFSIZE 4096

typedef struct sockaddr* Addr;

int main(int argc,char* argv[]){

    struct sockaddr_in seraddr,cliaddr;
    char buf[BUFFSIZE];
    int n,sockfd;
    socklen_t len;
    if(argc!=3){
        fprintf(stderr,"Usage: %s <ip> <port>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    //创建套接字
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    printf("create socket success!\n");
    
    //connect连接服务器
    memset(&cliaddr,0,sizeof(cliaddr));    
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(atoi(argv[2]));;
    cliaddr.sin_addr.s_addr = inet_addr(argv[1]);

    len =sizeof(cliaddr);
    if(connect(sockfd,(Addr)&cliaddr,len)<0){
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("connect success!\n");

    while(1){
        if(fgets(buf,sizeof(buf),stdin)==NULL){
            perror("fgets");
            break;
        }
        printf("%s\n",buf);
        send(sockfd,buf,sizeof(buf),0);
        if(strncmp(buf,"quit",4)==0){
            break;
        }
    }

    close(sockfd);
    return 0;
}
