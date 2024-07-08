#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000],client_message[2000];
    int server_struct_length = sizeof(server_addr);

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    //create socket:
    socket_desc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully.\n");

    //set port and ip:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //send message to server:
    strcpy(client_message,"send time");
    if(sendto(socket_desc,client_message,strlen(client_message),0,(struct sockaddr*)&server_addr,server_struct_length) < 0)
    {
        printf("Couldn't send the message.\n");
        return -1;
    }

    //recieve reply message from server:
    if(recvfrom(socket_desc,server_message,sizeof(server_message),0,(struct sockaddr*)&server_addr,&server_struct_length) < 0)
    {
        printf("Couldn't receive the message.\n");
        return -1;
    } 
    printf("server's s/m time: %s\n",server_message);
    
    close(socket_desc);
}   

/*
        OUTPUT
Socket created successfully.
server's s/m time: 2024-07-08 16:39:35(Its my system time check yours)
*/