#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int sockfd,ch,frame_id = -1;
int sequence_number = 0;
int n,m;

void* senddata(){
    char ch = 'D';
    while (1){
        frame_id++;
        write(sockfd, &ch, 1);
        write(sockfd, &frame_id,1);
        printf("Data send %d..\n",frame_id);
        sleep(1);
    }
}

void* receivedata() {
    char ack_info;
    while (1){
        n = read(sockfd,&ack_info,1);
        m = read(sockfd,&sequence_number,1);
        
        if(ack_info == 'A'){
            printf("ack received %d",sequence_number);
            sleep(1);
        } else if (ack_info == 'C'){
            printf("Sending Again..\n");
            frame_id = sequence_number - 1;
        }
    }
    
}

int main() {
    pthread_t send, receive;

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = 8888;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    connect(sockfd, (struct  sockaddr*)&server, sizeof(server));

    printf("Connecting to server...\n");
     
    pthread_create(&send, 0, senddata, 0);
    sleep(1);

    pthread_create(&receive, 0, receivedata, 0);
    sleep(1);

    while (1);
    
}