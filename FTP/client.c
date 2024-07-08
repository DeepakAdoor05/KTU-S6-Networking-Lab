#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) {
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    // Get input (file name) from user:
    printf("Enter file name: ");
    gets(client_message);

    // Send the file name to the server:
    if (send(socket_desc, client_message, strlen(client_message), 0) < 0) {
        printf("Unable to send file name\n");
        return -1;
    }

    // Receive the server's response (file contents):
    if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0) {
        printf("Error while receiving file contents\n");
        return -1;
    }

    printf("Server's response:\n%s\n", server_message);

    close(socket_desc);
    return 0;
}

/*
        OUTPUT
Socket created successfully
Connected with server successfully
Enter file name: hello.txt
Server's response:
Hi, How are You ?
I hope You are fine.
*/