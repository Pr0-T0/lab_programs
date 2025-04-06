#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>

int main(){

    int sockfd;
    struct sockaddr_in server;
    char buff[2040];

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_port = 7777;
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    sprintf(buff, "%s", "time");
    sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&server, sizeof(server));


    int len = sizeof(server);
    recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&server, &len);

    printf("Current time is %s",buff);;

    close(sockfd);
}
