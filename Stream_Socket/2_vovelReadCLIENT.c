#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("USAGE: ./A.OUT PORT_NUM\n");
		return 0;
	}

	int sockfd, newsfd;
	char rdbuf[128], wrbuf[128];
	struct sockaddr_in srv, cln;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket");
		return 0;
	}
	printf("SOCKET CREATED....\n");

	srv.sin_family=AF_INET;
	srv.sin_port=htons(atoi(argv[1]));
	srv.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(sockfd,(struct sockaddr*)&srv,sizeof(srv))!=0){
		perror("listen");
		return 0;
	}



	while(1){
		printf("ENTER STRING : \n");
		scanf("%s",wrbuf);
		write(sockfd,wrbuf,strlen(wrbuf)+1);
		read(sockfd,rdbuf,sizeof(rdbuf));
		printf("READ:: %s\n",rdbuf);
	}

}
