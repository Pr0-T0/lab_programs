#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<string.h>

int main(){
    char buff[1024];
    struct sockaddr_in server, client;
    time_t ct;
    int sockfd = socket(AF_INET,SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 7777;
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    int len = sizeof(client);

    while(1){
        recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client, &len);
        printf("Request From Client");

        ct  = time(NULL);
        sprintf(buff, "%s", ctime(&ct));

        sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client, sizeof(client));
        memset(buff, 0, sizeof(buff));    
    }
    close(sockfd);
}
