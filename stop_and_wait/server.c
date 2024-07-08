#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	char buf[100];
	int k;
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=3003;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");
    
    // Listen for clients:
    if(listen(socket_desc, 1) < 0){
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections...\n");
    
	client_size=sizeof(client_addr);
	client_sock=accept(socket_desc,(struct sockaddr*) &client_addr,&client_size);
		
    if (client_sock < 0){
        printf("Can't accept\n");
        return -1;
    }
	printf("Server accepted client\n\n");
	
	k = recv(client_sock,buf,100,0);
	int nof = atoi(buf);
    
	for(int i=0;i<nof;i++)
	{	if(i%2==0){
			k=recv(client_sock,buf,100,0);
			printf("Frame received from Client:Frame [0]\n");
			sleep(1);
		}
		else
		{
			k=recv(client_sock,buf,100,0);
			printf("Frame received from Client:Frame [1]\n");
			sleep(1);
		}
		printf("Acknowledgement for Frame [%d]\n",(i%2==0)?1:0);
		k=send(client_sock,buf,100,0);
		printf("\n");
	}
	return 0;
}

/*
		OUTPUT
Socket created successfully
Done with binding

Listening for incoming connections...
Server accepted client

Frame received from Client:Frame [0]
Acknowledgement for Frame [1]

Frame received from Client:Frame [1]
Acknowledgement for Frame [0]
*/