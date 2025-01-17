#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include  <arpa/inet.h>
int main(void)
{

    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];

    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

	// Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//send connection request to server:
    if(connect(socket_desc,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    //get input from user:
    printf("Enter message:");
    gets(client_message);

    //send the messsage to the server:
    if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("Unable to send message\n");
        return -1;
    }
    printf("Message sent to server\n");
    //receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }
    printf("Server's response: %s\n",server_message);

    // close the socket
    close(socket_desc);
    return 0;
}

/*
        OUTPUT
Socket created successfully
Connected with server successfully
Enter message:I am Client
Message sent to server
Server's response: I am Server
*/