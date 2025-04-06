#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
    int kind;
    int sequence_number;
    int acknowledgement;
    Packet packet;
}Frame;

int main() {
    int frame_id = 0;
    int ack_received = 1;
    Frame frame_received;
    Frame frame_send;
    frame_send.sequence_number = 0;

    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = 8888;
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    while(frame_send.sequence_number < 6){
        if (ack_received == 1){
            frame_send.sequence_number = frame_id;
            frame_send.kind = 1;
            frame_send.acknowledgement = 0;

            printf("Enter the data to send : ");
            scanf("%s", frame_send.packet.data);

            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&server, sizeof(server));
            printf("[+] Frame Send!");
        }
        int len = sizeof(server);
        recvfrom(sockfd, &frame_received, sizeof(Frame), 0, (struct sockaddr*)&server, &len);
        if(frame_received.sequence_number == 0 && frame_received.acknowledgement == frame_id + 1){
            printf("[+]Acknowledgement received!");
            ack_received = 1;
            frame_id++;
        }else {
            printf("[-] Acknowledgement not received, resending...");
            ack_received = 0;
        }
    }
    close(sockfd);
    return 0;
}