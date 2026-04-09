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
	srv.sin_addr.s_addr=inet_addr("0.0.0.0");
	if(bind(sockfd,(struct sockaddr*)&srv,sizeof(srv))!=0){
		perror("bind");
		return 0;
	}
	printf("PORT ADDRESS BIND COMPLETED...\n");

	if(listen(sockfd,1)!=0){
		perror("listen");
		return 0;
	}
	printf("LISTENING FOR CLIENT...\n");

	int clen=sizeof(cln);
	newsfd=accept(sockfd,(struct sockaddr*)&cln,&clen);
	if(newsfd<0){
		perror("accept");
		return 0;
	}
	printf("NEW CONNECTION ESTABLISHED>>>>\n");

	while(1){
		if(read(newsfd,rdbuf,sizeof(rdbuf))==0){
			printf("CLIENT TERMINATED...\n");
			break;
		}
		else{
			printf("%s\n",rdbuf);
			//vovel//
			int j=0;
		
		for(int i = 0; rdbuf[i]; i++) {
	    		if(rdbuf[i]=='a' || rdbuf[i]=='e' || rdbuf[i]=='i' || rdbuf[i]=='o' || rdbuf[i]=='u' || rdbuf[i]=='A' || rdbuf[i]=='E' || rdbuf[i]=='I' || rdbuf[i]=='O' || rdbuf[i]=='U') {
		        wrbuf[j++] = rdbuf[i];
		    }
		}

		wrbuf[j] = '\0';  // null terminate
		write(newsfd, wrbuf, strlen(wrbuf) + 1);
		}
	}
	exit(0);

}
