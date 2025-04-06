#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>

int main(){
	char buff[100];
	int status, sockfd;
	struct sockaddr_in client;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
	
	if(sockfd == -1){
		printf("Error in socket Creation..");
		exit(0);
	}

	client.sin_family = AF_INET;			//Configure Client
	client.sin_port = htons(3002);
	client.sin_addr.s_addr = INADDR_ANY; 

	status = connect(sockfd, (struct sockaddr*)&client, sizeof(client));

	if(status == -1){
		printf("Error in Connecting to server");
		exit(0);
	}

	while(1){
		printf("Enter the data to be send to server : ");
		fgets(buff, 100, stdin);
		if(strncmp(buff, "end", 3) == 0)
			break;
		
		status = send(sockfd, buff, 100, 0);

		if(status == -1){
			printf("Error in Sending Data to server");
			exit(0);
		}

		status = recv(sockfd, buff, 100, 0);
		
		if(status == -1){
			printf("Error in Receiving From server");
			exit(0);
		}
		printf("Message got from server is : %s",buff);
	}
	close(sockfd);
	return 0;
}
