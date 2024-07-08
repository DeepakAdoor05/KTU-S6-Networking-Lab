#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    int socket_desc;
    struct sockaddr_in server_addr,client_addr;
    char server_message[2000],client_message[2000];
    int client_struct_length = sizeof(client_addr);

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    socket_desc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socket_desc<0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Couldn't bind to the socket\n");
        return -1;
    }
    printf("Binding Done\n");
    printf("Listening for incoming message....\n");

    if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struct_length)<0)
    {
        printf("Couldn't receive the message\n");
        return -1;
    }
    printf("Msg from client: %s\n",client_message);

    printf("Enter the message:");
    gets(server_message);

    if(sendto(socket_desc,server_message,strlen(server_message),0,(struct sockaddr*)&client_addr,client_struct_length)<0)
    {
        printf("Couldn't send the message\n");
        return -1;
    }
    printf("Message sent to the client\n");

    close(socket_desc);
    return 0;
}

/*
        OUTPUT
Socket created successfully
Binding Done
Listening for incoming message....
Msg from client: I am Client
Enter the message:I am Server
Message sent to the client
*/