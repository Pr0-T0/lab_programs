#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd, client_1_len, client_2_len, temp_socket_1, temp_socket_2;
    int send_bytes, recv_bytes;
    struct sockaddr_in server, client_1,client_2;
    char buff[2040];

    server.sin_family = AF_INET;
    server.sin_port = htons(3002);
    server.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 2);

    client_1_len = sizeof(client_1);
    client_2_len = sizeof(client_2);

    temp_socket_1 = accept(sockfd, (struct sockaddr*)&client_1, &client_1_len);
    printf("Client Connnected : %s",inet_ntoa(client_1.sin_addr));

    temp_socket_2 = accept(sockfd, (struct sockaddr*)&client_2, &client_2_len);
    printf("Client Connected : %s",inet_ntoa(client_2.sin_addr));

    if(fork() == 0){
        while(1){
            bzero(buff, sizeof(buff));
            send_bytes = read(temp_socket_1, buff, sizeof(buff));
            write(temp_socket_2,buff, send_bytes);
        }
    }else {
        while(1){
            bzero(buff, sizeof(buff));
            recv_bytes = read(temp_socket_2, buff,sizeof(buff));
            write(temp_socket_1, buff, recv_bytes);
        }
    }
    close(temp_socket_1);
    close(temp_socket_2);
    close(sockfd);
    return 0;
}