#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
int main()

{
	char buf[100];
	int k,nof;
	int socket_desc;
	struct sockaddr_in server_addr;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=3003;
	server_addr.sin_addr.s_addr=INADDR_ANY;

    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");
    
	printf("Enter the total number of frames:");
	scanf("%d",&nof);
	printf("\n");
	
	sprintf(buf,"%d", nof);
	k = send(socket_desc,buf,100,0);
    
	for(int i=0;i<nof;i++)
	{
		if(i%2==0){
			printf("Frame [0] Sent\n");
			k=send(socket_desc,buf,100,0);
			sleep(1);
		}
		else
		{
			printf("Frame [1] Sent\n");
			k = send(socket_desc,buf,100,0);
			sleep(1);
		}
		printf("Acknowledgement received from server for Frame [%d]\n",(i%2==0)?1:0);
		k=read(socket_desc,buf,100);
		printf("\n");
	}
	close(socket_desc);
	return 0;
}

/*
		OUTPUT
Socket created successfully
Connected with server successfully
Enter the total number of frames:2

Frame [0] Sent
Acknowledgement received from server for Frame [1]

Frame [1] Sent
Acknowledgement received from server for Frame [0]
*/