#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAX 1024
#define SERV_TCP_PORT 8000

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in server;
    char str[MAX];

    if(argc != 3){
        printf("Usage : %s <Server IP><File Name>\n",argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        perror("Error in socket creation");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERV_TCP_PORT);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int status = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if (status == -1){
        printf("Error in connecting..");
        close(sockfd);
        exit(1);
    }

    strcpy(str, argv[2]);
    write(sockfd,str,  strlen(str) + 1);

    printf("File Contents Received ... \n");
    while(1){
        int n = read(sockfd, str, MAX);
        if (n <= 0) break;
        printf("%s",str);
    }

    printf("File Trnsfer Complete\n");

    close(sockfd);

    return 0;
}