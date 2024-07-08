#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr,client_addr;
    char server_message[2000],client_message[2000];
    int client_struct_length = sizeof(client_addr);

    //Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    //Create socket:
    socket_desc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return  -1;
    }
    printf("Socket created successfully.\n");

    //Set port and ip:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Bind it set port and ip:
    if (bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        printf("Couldn't bind to the port.\n");
        return -1;
        
    }
    printf("Binding Done.\n");
    while(1)
    {
        printf("Listening for incoming messages........\n");
        //Recieve the message from client:
        if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struct_length) < 0)
        {
            printf("Couldn't receive the message.\n");
            return  -1;
        } 
        printf("Received request from client:%s\n",client_message);
        //To get the indian time:
        setenv("TZ","Asia/kolkata",1);
        tzset();
        //Get the current time:
        time_t current_time;
        time(&current_time);
        struct tm *local_time = localtime(&current_time);
        strftime(server_message,sizeof(server_message),"%Y-%m-%d %H:%M:%S",local_time);
        printf("Sending time: %s\n",server_message);
        //send current time to client
        if(sendto(socket_desc,server_message,strlen(server_message),0,(struct sockaddr*)&client_addr,client_struct_length) < 0)
        {
            printf("Couldn't send the message.\n");
            return  -1;
        }
    }
    close(socket_desc);
}   

/*
        OUTPUT
Socket created successfully.
Binding Done.
Listening for incoming messages........
Received request from client:send time
Sending time: 2024-07-08 16:39:35
Listening for incoming messages........(Executes infinite times)
*/