#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <srv_ip> <srv_port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*1. 创建套接字*/
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socket.........\n");

	/*2. 主动向服务器发起连接请求*/
	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(atoi(argv[2]));
	srv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if (0 > connect(sockfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr))) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	printf("connect........\n");

	/*3. 数据的收发*/
	char buf[1024];
	while (1) {
		fgets(buf, sizeof(buf), stdin);
		if (0 > send(sockfd, buf, sizeof(buf), 0)) {
			perror("send");
			break;
		}
	}

	/*4. 关闭套接字*/
	close(sockfd);


	return 0;
}
