#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame
{
    int kind;
    int sequence_number;
    int acknowledgement;
    Packet packet;
}Frame;


int main() {
    int frame_id = 0;
    Frame frame_receive;
    Frame frame_send;

    int sockfd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = 8888;
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    int len = sizeof(client);

    while(1){
        recvfrom(sockfd, &frame_receive, sizeof(Frame), 0, (struct sockaddr*)&client, &len);

        if(frame_receive.kind == 1 && frame_receive.sequence_number == frame_id){
            printf("[+] Frame Received : %s\n",frame_receive.packet.data);
            frame_send.sequence_number = 0;
            frame_send.kind = 0;
            frame_send.acknowledgement = frame_receive.sequence_number + 1;

            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&client, sizeof(client));
            printf("[+] Ack Send\n");
        }else {
            printf("[-] Frame not Receivedn");
        }
        frame_id++;
    }
    close(sockfd);
    return 0;
}