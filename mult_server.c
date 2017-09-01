#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include<unistd.h>

void handler(int sigo)
{
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char *argv[])
{

	/*1. 创建套接字*/
    int sockfd;
    int connfd;
    struct sockaddr_in cliaddr;
    int addrlen = sizeof(cliaddr);
    pid_t pid;
    char buf[1024];
    int ret;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sockfd) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socket.........\n");

	/*2. 绑定本机地址和端口*/
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family 	= AF_INET;
	myaddr.sin_port 	= htons(8000);
	myaddr.sin_addr.s_addr 	= htonl(INADDR_ANY);  

	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("bind........\n");

	/*3. 设置监听套接字*/
	if (0 > listen(sockfd, 8)) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("listen...........\n");
    //异步函数，放在“那”都关系不大
	signal(SIGCHLD, handler);

	while (1) {
		/*4. 接收客户端连接，并生成通信套接字*/
		if (0 > (connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &addrlen))) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("accept client: %s\n", inet_ntoa(cliaddr.sin_addr));

        if((pid=fork())<0){
            perror("fork");
            break;
        }

        else if(pid==0){
            //关闭子进程的套接字
            //close(sockfd);
            while(1){
                ret = recv(connfd,buf,sizeof(buf),0);
                if(ret<0){
                    perror("recv");
                    break;
                }
                else if(ret==0){
                    printf("write close!.............\n");
                    break;
                }
                write(STDOUT_FILENO,buf,strlen(buf));
            }
            close(connfd);
            exit(EXIT_SUCCESS);
        }
        else{
            close(connfd);
        }
        
    }
        close(sockfd);
        return 0;
}

        


