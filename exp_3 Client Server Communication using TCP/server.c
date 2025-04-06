#include<stdio.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>

int main(){
    char buff[100];
    int status, sockfd, temp;
    struct sockaddr_in server,client;
    socklen_t len;

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    sockfd = socket(AF_INET,SOCK_STREAM, 0);

    if(sockfd == -1){
        printf("Error in Socket Creation..");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(3002);
    server.sin_addr.s_addr = INADDR_ANY;

    status = bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    if(status == -1){
        printf("Error In Binding..");
        exit(1);
    }

    status = listen(sockfd, 20);

    if(status == -1){
        printf("Error In Listening..");
        exit(1);
    }

    len = sizeof(client);
    temp = accept(sockfd, (struct sockaddr*)&client, &len);
    
    if(temp == -1){
        printf("temporary Socket Creation Failed..");
        exit(1);
    }

    while(1){
        status = recv(temp, buff, 100, 0);

        if(status == -1){
            printf("Error In Receiving..");
            exit(1);
        }

        printf("Message got From Client is : %s",buff);

        printf("Enter the data to send : ");
        fgets(buff, 100, stdin);

        if(strncmp(buff, "end", 3) == 0)
            break;
        
        status = send(temp, buff, 100, 0);

        if(status == -1){
            printf("Error in sending..");
            exit(1);
        }
    }
    close(sockfd);
    return 0;
}