#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<strings.h>
#include<stdlib.h>	//exit(0)


int prime(int n){
	int num = n, count=0;
	while(num!=0){
		if(n%num == 0){
			count++;
			num--;
		}
		else 
			num --;
	}
		if(count==2){
			return n;
		}
		else 
			return 0;
}

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("USAGE: ./a.out Port_num\n");
		return 0;
	}
	char rdbuf[128];
	int sockfd,newsfd, a, arr[10], i=0;
	struct sockaddr_in srv, cln;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket");
		return 0;
	}
	printf("SOCKET CREATED SUCCESSFULLY....\n");
	int port = gen_num(argv[1]);
	srv.sin_family=AF_INET;
	srv.sin_port=htons(port);
	srv.sin_addr.s_addr=inet_addr("0.0.0.0");

	if(bind(sockfd,(struct sockaddr*)&srv, sizeof(srv))!=0){
		perror("bind");
		return 0;
	}
	printf("BINDING ADDRESS SUCCESSFUL!!!\n");

	if(listen(sockfd,1)!=0){
		perror("listen");
		return 0;
	}
	printf("SERVER LISTENING.-.-.\n");

	int ClnLen= sizeof(cln);
	newsfd=accept(sockfd,(struct sockaddr*)&cln,&ClnLen);
	if(newsfd<0){
		perror("accept");
		return 0;
	}

	printf("New client connection accepted...\n");
	
	while(1){
		bzero(&a,sizeof(int));
		if(read(newsfd,&a,sizeof(int))==0){
			printf("client terminated\n");
			break;
		}
			printf("RECEIVED: %d \n",a);
			int num = prime(a);
			if(num!=0){
				arr[i] = num;
				i++;
			}
			write(newsfd,arr,sizeof(arr));
			
	}
	exit(0);
}
