#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>

int main(){

    char buff[2040];
    int sockfd, send_data_bytes, recv_data_bytes;
    struct sockaddr_in server;

    sockfd = socket(AF_INET,SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(3002);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(sockfd, (struct sockaddr*)&server , sizeof(server));

    printf("Server Connected!");

    if(fork() == 0) {

        while (1){
            bzero(buff, sizeof(buff));
            send_data_bytes = read(0, buff, 2040);
            write(sockfd, buff, send_data_bytes);   
        }
    }// child Process

    else{
        while (1){
            bzero(buff, sizeof(buff));
            recv_data_bytes = read(sockfd, buff, 2040);
            write(1, buff,recv_data_bytes);
        }
    }//parant process
    close(sockfd);
    return 0;
}
