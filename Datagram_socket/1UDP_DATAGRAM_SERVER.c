#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("USAGE: ./a.out port_num\n");
        return 0;
    }

    char rdbuf[128];
    int sockfd;
    struct sockaddr_in srv, cln;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        perror("socket");
        return 0;
    }
    printf("SOCKET CREATED..\n");

    //memset(&srv, 0, sizeof(srv));
    //memset(&cln, 0, sizeof(cln));

    srv.sin_family = AF_INET;
    srv.sin_port = htons(atoi(argv[1]));
    srv.sin_addr.s_addr = INADDR_ANY;	//INADDR_ANY = 0.0.0.0

    if(bind(sockfd, (struct sockaddr*)&srv, sizeof(srv)) != 0){
        perror("bind");
        return 0;
    }
    printf("BIND SUCCESSFUL\n");

    printf("WAITING FOR CLIENT DATA...\n");

    int len = sizeof(cln);

    int n = recvfrom(sockfd, rdbuf, sizeof(rdbuf), 0,
                     (struct sockaddr*)&cln, &len);
    if(n < 0){
        perror("recvfrom");
        return 0;
    }

    rdbuf[n] = '\0';
    printf("RECEIVED: %s\n", rdbuf);

    close(sockfd);
}
