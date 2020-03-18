#include <stdio.h>
#define INFINITE 10000
#define MAX 100


void all_pairs(int A[MAX][MAX], int D[MAX][MAX], int vertices) {
    int i,j,k;
    for(i=1; i<=vertices ; i++)
    {
        for(j=1 ; j<=vertices ; j++)
        {
            for(k=1 ; k<=vertices ; k++)
            {
                if(A[i][j] > A[i][k] + A[k][j])
                {
                    D[i][j] = k;
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }

    printf("\nA Array\n");
    for(i=1; i<=vertices ; i++){
        for(j=1 ; j<=vertices ; j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    printf("\nD Array\n");
    for(i=1; i<=vertices ; i++){
        for(j=1 ; j<=vertices ; j++){
            printf("%d ",D[i][j]);
        }
        printf("\n");
    }
}

int find_parent(int D[MAX][MAX],int i, int j){
    return D[i][j];
}

void display_path(int A[MAX][MAX], int D[MAX][MAX], int source, int destination, int vertices){
    int path[MAX];
    int count=0;
    int i;
    int destination_copy = destination;
    while(destination != source) {
        path[count] = find_parent(D,source,destination);
        destination = find_parent(D,source,destination);
        count++;
    }
    printf("\n");
    for(i=count-1;i>=0;i--)
        printf("%d-",path[i]);
    printf("%d",destination_copy);
    printf("\nCost = %d",A[source][destination_copy]);
}


void main() {
    int i,j,k;
    int edges;
    int A[MAX][MAX];
    int D[MAX][MAX];
    int u,v,w;
    int vertices;
    int choice;
    int source,destination;

    printf("\nEnter Vertices: ");
    scanf("%d",&vertices);
    printf("\nEnter no of Edges: ");
    scanf("%d",&edges);
    printf("\nEnter edges in the format: U V W\n");

    for(i=1; i<=vertices ;i++)
        for(j=1; j<=vertices ;j++)
            A[i][j] = INFINITE;

    for(i=1 ; i<=edges ; i++){
        scanf("%d%d%d",&u,&v,&w);
        A[u][v] = w;
    }

    for(i=1; i<=vertices ; i++)
        A[i][i] = 0;

    for(i=1; i<=vertices ; i++) {
        for(j=1; j<=vertices ; j++) {
            if((i==j) || (A[i][j] == INFINITE))
                D[i][j] = -1;
            else
                D[i][j] = i;
        }
    }

    all_pairs(A,D,vertices);

    while(1) {
        printf("\n----------------------------\n");
        printf("\n1.Find Path\n2.Exit\n");
        scanf("%d",&choice);
        if(choice == 2) {
            break;
        }
        printf("\nEnter Source: Destination:\n");
        scanf("%d %d",&source,&destination);
        display_path(A,D,source,destination,vertices);
    }
}