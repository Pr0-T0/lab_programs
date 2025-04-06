#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>

int main(){
	char buff[100];
	int status, sockfd;
	struct sockaddr_in server;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
	
	if(sockfd == -1){
		printf("Error in socket Creation..");
		exit(0);
	}

	server.sin_family = AF_INET;			//Configure Server details for connecting the Client
	server.sin_port = htons(3002);
	server.sin_addr.s_addr = INADDR_ANY; 

	status = connect(sockfd, (struct sockaddr*)&server, sizeof(server));

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
