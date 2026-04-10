#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("USAGE: ./a.out port_num\n")
		return 0;
	}

	int i;
	char rdbuf[128];
	int sockfd, newsfd;
	struct sockaddr_in srv, cln;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket");
		return 0;
	}
	printf("SOCKET CREATED.....\n");

	srv.sin_family = AF_INET;
	srv.sin_port = htons(atoi(argv[1]));
	srv.sin_addr.s_addr = inet_addr("0.0.0.0");

	if(bind(sockfd,(struct sockaddr*)&srv,sizeof(srv))!=0){
		perror("bind");
		return 0;
	}
	printf("BINDING OF PORT+IP ADDRESS(DONE)*****\n");

	if(listen(sockfd,1)!=0){
		perror("listen");
		return 0;
	}

	int len = sizeof(cln);

	while(1){
		newsfd = accept(sockfd,(struct sockaddr*)&cln,&len);
		if(newsfd<0){
			perror("accept");
			return 0;
		}
		printf("NEW CLIENT CONNECTED ");

		if(fork()==0){
			while(1){
				bzero(rdbuf,128);
				if(read(newsfd,rdbuf,128)==0){
					printf("client terminated...\n");
					break;
				}
				printf("RECEIVED: %s\n",rdbuf);
			}
		}
		else
			 close(newsfd);
	}
}
