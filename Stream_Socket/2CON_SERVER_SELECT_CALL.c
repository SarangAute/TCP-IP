#include<stdio.h>
#include<netinet/in.h>	//struct sockaddr_in
#include<string.h>	//str
#include<unistd.h>	//read()
#include<stdlib.h>	//atoi()
#include<arpa/inet.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("./a.out port_num\n");
		return 0;
	}

	int i;
	char rdbuf[128];
	fd_set rdset, testset;	//fd_set is fixed size buffer
	printf("%ld\n",sizeof(rdset));
	int sfd, newsfd;
	struct sockaddr_in server, client;
	
	sfd = socket(AF_INET, SOCK_STREAM,0);
	if(sfd<0){
		perror("socket");
		return 0;
	}

	server.sin_family=AF_INET;	//IPV4 = AF_INET
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=inet_addr("0.0.0.0");

	if(bind(sfd,(struct sockaddr*)&server, sizeof(server))==0)
		printf("bind : successful");
	else{
		perror("bind");
		return 0;
	}

	listen(sfd,1);
	int len;
	len=sizeof(client);
	FD_ZERO(&rdset);
	FD_SET(sfd,&rdset);

	while(1){
		testset=rdset;
		select(100,&testset,0,0,0);
		for(i=0;i<100;i++){
			if(FD_ISSET(i,&testset))
				break;
		}
		if(sfd==i){
			printf("new connection...\n");
			newsfd=accept(sfd,(struct sockaddr*)&client,&len);
			FD_SET(newsfd,&rdset);
		}
		else{
			bzero(rdbuf,128);
			read(i,rdbuf,128);
			printf("%s\n",rdbuf);
		}	
	}
}
