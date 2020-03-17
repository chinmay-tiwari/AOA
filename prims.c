//PRIMS
#include <stdio.h>
#define MAX 50

int min_vertex_(int weight[], int visited[], int n) {
    int min_vertex = -1;
    int i;
    for(i=1 ; i<=n ;i++) {
        if(visited[i] == 0 && (min_vertex == -1 || (weight[i] < weight[min_vertex])))
            min_vertex = i;
    }
    return min_vertex;
}

void prims(int edge_weight[MAX][MAX], int n) {
    int i,j;
    int parent[MAX];
    int visited[MAX];
    int weight[MAX];

    for(i = 1; i<=n ; i++) {
        visited[i] = 0;
        weight[i] = 30000;
    }

    weight[1] = 0;
    parent[1] = -1;

    for(i = 1; i<=n ;i++) {
        int min_vertex;
        min_vertex = min_vertex_(weight,visited,n);
        visited[min_vertex] = 1;
        for(j=1; j<=n ;j++) {
            if(visited[j] == 0 && edge_weight[min_vertex][j] != 0){
                if(edge_weight[min_vertex][j] < weight[j]) {
                    weight[j] = edge_weight[min_vertex][j];
                    parent[j] = min_vertex;
                }
            }
        }
    }

    printf("\nMCST is formed!\n");
    for(i = 2;  i<=n ;i++) {
        if(i < parent[i])
            printf("\nSource:%d Destination:%d Weight:%d",i,parent[i],weight[i]);
        else
            printf("\nSource:%d Destination:%d Weight:%d",parent[i],i,weight[i]);
    }
}

void main() {
    int i,j;
    int src,dest,w;
    int vertices,edges;
    int adjacency[MAX][MAX];
    int weight[MAX][MAX];
    printf("\nEnter number of vertices:\n");
    scanf("%d",&vertices);
    printf("\nEnter number of edges:\n");
    scanf("%d",&edges);
    printf("Enter edges in the format src,dest,weight:\n");
    for(i = 1; i<=edges ; i++) {
        scanf("%d %d %d",&src,&dest,&w);
        adjacency[src][dest] = adjacency[dest][src] = 1;
        weight[src][dest] = weight[dest][src] = w;
    }
    prims(weight, vertices);
}