#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) {
    int socket_desc, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];
    int client_size = sizeof(client_addr);
    FILE* file;

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

    if (bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    if (listen(socket_desc, 1) < 0) {
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections...\n");

    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
    if (client_sock < 0) {
        printf("Can't accept\n");
        return -1;
    }
    //printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    // Receive the file name from the client:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0) {
        printf("Error while receiving file name\n");
        return -1;
    }
    printf("Client requested file name :%s\n",client_message);
    // Open the file (assuming it's in the same directory as the server):
    file = fopen(client_message, "r");
    if (file == NULL) {
        strcpy(server_message, "File not found.");
    } else {
        // Read file contents:
        fread(server_message, sizeof(char), sizeof(server_message), file);
        fclose(file);
    }

    // Send the file contents back to the client:
    if (send(client_sock, server_message, strlen(server_message), 0) < 0) {
        printf("Can't send file contents\n");
        return -1;
    }
    printf("File transfered\n");

    close(client_sock);
    close(socket_desc);

    return 0;
}

/*
        OUTPUT
Socket created successfully
Done with binding

Listening for incoming connections...
Client requested file name :hello.txt
File transfered
*/