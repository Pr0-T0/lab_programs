#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAX 1024
#define SERV_TCP_PORT 8000

int main(){
    FILE *f1;
    int sockfd, newsockfd, clength;
    struct sockaddr_in server, client;
    char buff[MAX],str[MAX];

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("error in socket creation");
        exit(1);
    } else {
        printf("Socket created..");
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERV_TCP_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int status = bind(sockfd,(struct sockaddr*)&server, sizeof(server));

    if(status == -1){
        perror("Erorr in binding..");
        close(sockfd);
        exit(1);
    } else {
        printf("Binded!");
    }

    printf("Listening....");
    listen(sockfd, 5);


    clength = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr*)&client, &clength);

    if(newsockfd == -1){
        perror("Error in accept..");
        close(sockfd);
        exit(1);
    }

    close(sockfd);

    read(newsockfd, str, MAX);
    printf("Client Message\nFile Name : %s\n",str);

    f1 = fopen(str, "r");
    if(f1 == NULL){
        perror("Error opening File");
        close(newsockfd);
        exit(1);
    }
    while(fgets(buff, sizeof(buff),f1)!= NULL){
        write(newsockfd, buff, strlen(buff));
    }

    fclose(f1);
    printf("File Transferred....\n");
    close(newsockfd);

    return 0;
}