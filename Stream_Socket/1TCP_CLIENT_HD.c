#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
unsigned int gen_num(const char* s){
        unsigned int num = 0;
        int i=1;
        while(*s)
                num+= (*s++ * i++);
        return(num%(49151-1024+1))+1024;
}


int main(int argc, char* argv[]){
	if(argc!=2){
		printf("USAGE: ./a.out ServerName\n");
		return 0;
	}

	char wrbuf[128];
	int sockfd;
	struct sockaddr_in srv;
	sockfd=socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket");
		return 0;
	}
	printf("SOCKET CREATED SUCCESSFULLY....\n");
	
	int port=gen_num(argv[1]);
	srv.sin_family=AF_INET;
	srv.sin_port=htons(port);
	srv.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(sockfd,(struct sockaddr*)&srv,sizeof(srv))!=0){
		perror("connect");
		return 0;
	}
	printf("CONNECTED TO SERVER...\n");

	while(1){
		printf("ENTER DATA: ");
		scanf("%s",wrbuf);
		write(sockfd,wrbuf,strlen(wrbuf)+1);
	}
}
