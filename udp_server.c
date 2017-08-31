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
    //创建套接字
    struct sockaddr_in seraddr,cliaddr;
    char buf[BUFFSIZE];
    int n,sockfd;
    
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    printf("create sockfd success!\n");

    //绑定本地主机和端口号
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(6666);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if((bind(sockfd,(Addr)&seraddr,sizeof(seraddr)))<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind success!\n");

    //收发数据
    socklen_t len = sizeof(cliaddr);
    while(1){
        n=recvfrom(sockfd,buf,sizeof(buf),0,(Addr)&cliaddr,&len);
        printf("发送方地址是: %s\n", inet_ntoa(cliaddr.sin_addr));        
        if(n<0){
            perror("recvfrom");
            break;
        }
        else if(n>0){
            //write(STDOUT_FILENO,buf,n);
            printf("Reveice client:%s\n",buf);
        }
        else{
            //客户机关闭
            printf("The clien has closed!\n");
        }
        sendto(sockfd,buf,sizeof(buf),0,(Addr)&cliaddr,len);
    }

    //关闭套接字
    close(sockfd);
    return 0;
}
