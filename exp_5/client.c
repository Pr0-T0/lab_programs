#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>

int main(){

    int sockfd;
    struct sockaddr_in client;
    char buff[2040];

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    client.sin_family = AF_INET;
    client.sin_port = 7777;
    client.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&client, sizeof(client));

    sprintf(buff, "%s", "time");
    sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client, sizeof(client));


    int len = sizeof(client);
    recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client, &len);

    printf("Current time is %s",buff);;

    close(sockfd);
}