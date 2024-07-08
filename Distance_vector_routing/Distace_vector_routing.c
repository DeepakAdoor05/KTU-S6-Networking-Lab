#include <stdio.h>
int costMatrix[20][20],n,i,j,k;
struct routers
{
    int distance[20];
    int adjNode[20];
}node[20];

void readCostMatrix()
{
    printf("Enter the cost matrix: ");
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            scanf("%d",&costMatrix[i][j]);
            costMatrix[i][i] = 0;
            node[i].distance[j] = costMatrix[i][j];
            node[i].adjNode[j] = j;
        }
    }
}

void CalcRoutingTable()
{
    for (i=0; i < n; i++)
    {
        for (j=0; j < n; j++)
        {
            for (k=0; k < n; k++)
            {
                if (node[i].distance[j] > costMatrix[i][k] + node[k].distance[j])
                {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjNode[j] = k;
                }
                
            }
            
        }
    }
}

void DisplayMatrix()
{
    for ( i = 0; i < n; i++)
    {
        printf("Router: %d\n",i+1);
        printf("---------\n");
        for ( j = 0; j < n; j++)
        {
            printf("Node: %d via: %d Distance: %d\n",j+1,node[i].adjNode[j]+1,node[i].distance[j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("Number of Nodes: ");
    scanf("%d",&n);
    readCostMatrix();
    CalcRoutingTable();
    DisplayMatrix();
    return 0;
}

/*
    OUTPUT
Number of Nodes: 3
Enter the cost matrix: 0 1 2 1 0 3 2 3 0
Router: 1
---------
Node: 1 via: 1 Distance: 0
Node: 2 via: 2 Distance: 1
Node: 3 via: 3 Distance: 2

Router: 2
---------
Node: 1 via: 1 Distance: 1
Node: 2 via: 2 Distance: 0
Node: 3 via: 3 Distance: 3

Router: 3
---------
Node: 1 via: 1 Distance: 2
Node: 2 via: 2 Distance: 3
Node: 3 via: 3 Distance: 0
*/