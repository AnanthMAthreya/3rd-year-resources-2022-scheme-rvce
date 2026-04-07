#include <stdio.h>


struct node{
    unsigned front[20];
    unsigned dist[20];
}t[10];


int main()
{
    int costmat[20][20];
    int nodes,i,j,k,count=0;
    printf("\nEnter the no of nodes: ");
    scanf("%d",&nodes);
    printf("Enter the matrix:\n ");


    for(i=0;i<nodes;i++){
        for(j=0;j<nodes;j++){
            scanf("%d",&costmat[i][j]);
            costmat[i][i]=0;
            t[i].dist[j]=costmat[i][j];
            t[i].front[j]=j;
        }
    }


    // Relaxation
    do{
        count=0;
        for(i=0;i<nodes;i++)
            for(j=0;j<nodes;j++)
                for(k=0;k<nodes;k++)
                    if(t[i].dist[j]>costmat[i][k]+t[k].dist[j]){
                        t[i].dist[j]=t[i].dist[k]+t[k].dist[j];
                        t[i].front[j]=k;
                        count++;
                    }
    }while(count!=0);


    for(i=0;i<nodes;i++){
        printf("\nFor router %d ",i+1);
        for(j=0;j<nodes;j++){
            printf("\nFor node %d via %d distance is %d",j+1,t[i].front[j]+1,t[i].dist[j]);
        }
    }
    printf("\n\n");
    
   
}