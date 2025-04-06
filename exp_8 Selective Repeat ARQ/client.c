#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>

#define WSIZE 3
int sockfd,up = -1,low = 0;

void* senddata(){
    char ch = 'D';
    while(1){
        up++;
        while ((up -low) > WSIZE){
            printf("Congestion..");
            sleep(1);
        }
        printf("Data Send: %d\n",up);
        write(sockfd,&ch,1);
        write(sockfd,&up,1);
        sleep(1);
    }
}
void* receivedata() {
    int sequence_number;
    char ack_info;
    char ch = 'D';
    while (1){
        read(sockfd,&ack_info,1);
        read(sockfd,&sequence_number,1);
        
        if(ack_info == 'A'){
            printf("ack received %d",sequence_number);
            low++;
        } else if (ack_info == 'C'){
            printf("Sending Again..\n");
            write(sockfd,&ch,1);
            write(sockfd,&sequence_number,1);
        }
        sleep(1);
    }
    
}

int main() {
    pthread_t send, receive;

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = 8888;
    server.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    connect(sockfd, (struct  sockaddr*)&server, sizeof(server));

    printf("Connecting to server...\n");
     
    pthread_create(&send, 0, senddata, 0);
    sleep(1);

    pthread_create(&receive, 0, receivedata, 0);
    sleep(1);

    while (1);
}