#include<stdio.h>

int main()
{
    int incoming,outgoing,buck_size,n,store=0;
    printf("Enter the bucket size, outgoing rate and no: of inputs:");
    scanf("%d %d %d",&buck_size,&outgoing,&n);
    while (n!=0)
    {
        printf("Enter the incoming packet size:");
        scanf("%d",&incoming);
        printf("The incoming packet size is :%d\n",incoming);
        if (incoming <= (buck_size-store))
        {
            store += incoming;
            printf("Bucket size %d out of %d\n",store,buck_size);
        }
        else
        {
            printf("Dropped %d packets\n",incoming-(buck_size-store));
            printf("Bucket size %d out of %d\n",store,buck_size);
        }
        store -= outgoing;
        if (store < 0)
            store = 0;
        printf("After outgoing, %d left out of %d in buffer\n",store,buck_size);
        n--;
        printf("******************************************\n");
    }
}

/*
                OUTPUT
Enter the bucket size, outgoing rate and no: of inputs:10 3 3 
Enter the incoming packet size:2 
The incoming packet size is :2
Bucket size 2 out of 10
After outgoing, 0 left out of 10 in buffer
******************************************
Enter the incoming packet size:3
The incoming packet size is :3
Bucket size 3 out of 10
After outgoing, 0 left out of 10 in buffer
******************************************
Enter the incoming packet size:4
The incoming packet size is :4
Bucket size 4 out of 10
After outgoing, 1 left out of 10 in buffer
******************************************
*/