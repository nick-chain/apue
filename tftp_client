#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<dirent.h>
#include<unistd.h>
#define SIZE 128

void do_list(int connfd, char cmd[]){
    DIR* dir=opendir(".");
    struct dirent* fp;

    while((fp=readdir(dir))){
        send(connfd,fp->d_name,sizeof(fp->d_name),0);
    }
    closedir(dir);
}

void do_put(int connfd,char cmd[]){
	printf("%s\n",cmd+4);
	int fd = open(cmd+4, O_WRONLY|O_CREAT|O_TRUNC, 0666);	
	if(fd<0){
		perror("server open");
		send(connfd,"N",2,0);
		return;
	}
	else{
		send(connfd,"Y",2,0);
	}

	int n;
	char buf[SIZE];
	while(1){
		n =recv(connfd,buf,sizeof(SIZE),0);
		if(n<=0){
			break;
		}
		else{
			write(fd,buf,n);
		}
	}
	close(fd);
}

void do_get(int connfd,char cmd[]){
	int fd=open(cmd+4,O_RDONLY);
	if(fd<0){
		perror("server open");
		send(connfd,"N",2,0);
		return;
	}
	else{
		send(connfd,"Y",2,0);
	}

	int n;
	char buf[SIZE];
	while(1){
		n =read(fd,buf,SIZE);
		if(n<=0){
			break;
		}
		else{
			send(connfd,buf,n,0);
		}
	}
	close(fd);
}

int main()
{
	int sockfd, connfd;
	if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("create socket success!..............\n");
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family 	= AF_INET;
	myaddr.sin_port 	= htons(6666);
	myaddr.sin_addr.s_addr 	= inet_addr("127.0.0.1");
	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("bind success!...........\n");
	if (0 > listen(sockfd, 8)) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("listen success!.....................\n");
	char cmd[SIZE];
	while (1) {
		connfd = accept(sockfd, NULL, NULL);
		if (connfd < 0) {
			perror("accept");
			break;
		}
		printf("accept success!...............\n");
		recv(connfd, cmd, SIZE, 0);

		if (strncmp(cmd, "get ", 4) == 0)
			do_get(connfd, cmd);
		else if (strncmp(cmd, "put ", 4) == 0)
			do_put(connfd, cmd);
		else if (strcmp(cmd, "list") == 0)
			do_list(connfd,cmd);
		else 
			fprintf(stderr, "error\n");
		
		close(connfd);
	}
	close(sockfd);

	return 0;
}
