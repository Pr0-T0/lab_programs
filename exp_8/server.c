#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int sockfd, temp_socket;
    int data_m,data_n;
    int sequence_number;
    int random_number;
    int frame_id = -1;
    char can = 'C';
    char ca = 'A';
    char ch;
     
    sockfd = socket(AF_INET,SOCK_STREAM, 0);

    struct sockaddr_in server,client;

    server.sin_family = AF_INET;
    server.sin_port = 8888;
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    listen(sockfd, 5);

    printf("Server is Waiting..");
    int len = sizeof(client);
    temp_socket = accept(sockfd, (struct sockaddr*)&client, &len);

    while(1){
        read(temp_socket,&ch,1);
        read(temp_socket,&sequence_number,1);

        if(ch == 'D'){
            random_number = rand();
            if(random_number % 3 == 0){
                    printf("Data %d is corrupted..\n",frame_id);
                    write(temp_socket,&can,1);
                    write(temp_socket,&sequence_number,1);
                    sleep(2);
            } 
            else {
                    printf("data %d received..\n",sequence_number);
                    write(temp_socket,&ca,1);
                    write(temp_socket,&sequence_number,1);
                    frame_id = sequence_number;
            }
        }
    }
}
