//DIJKSTRAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 700
#define MAX_WEIGHT_LOW 1
#define MAX_WEIGHT_HIGH 1000

void create_graph(int vertices) {
	FILE *fp;
	int adjacency[1000][1000];
	int i,j;
	int max_edges = vertices*(vertices - 1)/2;
	int b;
	int interation_for_edges;
	int weight;
	fp = fopen("created_graph.txt","w");
	srand(time(NULL));

	for(i=1 ; i<=vertices ;i++) {
		interation_for_edges = rand() % max_edges;
		for(j = interation_for_edges; j<= max_edges ;j++) {
			b = rand() % (vertices+1);

			if(j == 0 || b == 0)
				continue;
			if(adjacency[i][b] != 0)
				continue;

			adjacency[i][b] = adjacency[b][i] = 1;
		}
	}

	for(i = 1; i<=vertices ;i++){
		for(j = i; j<=vertices ;j++){
			if(adjacency[i][j] == 1 && i!=j) {
				weight = (rand() % (MAX_WEIGHT_HIGH - MAX_WEIGHT_LOW + 1)) + MAX_WEIGHT_LOW;
				fprintf(fp,"%d %d %d\n",i,j,weight);
			}
		}
	}

	fclose(fp);
}

int accept_graph(int adjacency[MAX][MAX], int weight[MAX][MAX]) {
    FILE *fp;
    int i=0;
    int e;
    int src,dest,w;
    fp = fopen("created_graph.txt","r");
    while(feof(fp) != 1){
        fscanf(fp,"%d %d %d",&src,&dest,&w);
        adjacency[src][dest] = adjacency[dest][src] = 1;
        weight[src][dest] = weight[dest][src] = w;
        i++;
    }
    e = i - 1;
    return e;
    fclose(fp);
}

int min_vertex_(int weight[], int visited[], int n) {
    int min_vertex = -1;
    int i;
    for(i=1 ; i<=n ;i++) {
        if(visited[i] == 0 && (min_vertex == -1 || (weight[i] < weight[min_vertex])))
            min_vertex = i;
    }
    return min_vertex;
}

void path_print(int parent[], int weight[], int n) {
    int path[MAX];
    int i,j,k;
    int initial_vertex;
    for(i = 2 ; i<=n ;i++) {
        j = 0;
        initial_vertex = i;
        while(initial_vertex != 1) {
            path[j] = initial_vertex;
            initial_vertex = parent[initial_vertex];
            j++;
        }
        printf("\n");
        printf("1");
        for(k = j-1; k >= 0 ; k--){
            printf("-%d",path[k]);
        }
        printf(" Cost = %d",weight[i]);
    }
}

void dijkstra(int edge_weight[MAX][MAX], int n) {
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
                if(( edge_weight[min_vertex][j] + weight[min_vertex] )< weight[j]) {
                    weight[j] = edge_weight[min_vertex][j] + weight[min_vertex];
                    parent[j] = min_vertex;
                }
            }
        }
    }

    printf("\nGraph:\n");
    for(i = 2;  i<=n ;i++) {
            printf("\nSource:%d Destination:%d Weight:%d",i,parent[i],weight[i]);
    }

    printf("\nPath:\n");
    path_print(parent,weight,n);
}



int main() {
    FILE *fp;
    int i,j;
    int src,dest,w;
    int edges;
    int adjacency[MAX][MAX];
    int weight[MAX][MAX];
    double time_spent;
    int iteration;

    fp = fopen("readings.txt","w");

    for(iteration = 100; iteration < 700 ;iteration += 100) {
        create_graph(iteration);
        edges = accept_graph(adjacency,weight);
        clock_t begin = clock();
        dijkstra(weight, iteration);
        clock_t end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(fp,"\nVertices = %d Edges = %d\n",iteration,edges);
        fprintf(fp,"\nTime taken for Execution = %f\n",time_spent);
   }
    fclose(fp);
    return 0;
}