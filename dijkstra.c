#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define inf 	100000 	//Representing infinity

//--------------------------------
#define V_SIZE	256
#define NAME_FILE "data/test-21_256.txt" 
#define STARTING_NODE 0
//--------------------------------

//Array fill
void array_fill(int * array, int len, int val) {
	int i;
	for (i = 0; i < len; i++){ 
		array[i] = val; 
	}
}

/**
 * Input parameters：
 *	graph:	weight matrix
 *	n:		matrix size (number of nodes)
 *	start:	starting node
 *	dist:	where do we are going to put the distance of nodes
 * */
void dijkstra(int graph[][V_SIZE], int n, int start, int dist[]) {
	
	int* path=(int*)malloc(sizeof(int)*n);
	int* shortest=(int*)malloc(sizeof(int)*n);
	int* mark=(int*)malloc(sizeof(int)*n);
	int min, v, i, j;

	array_fill(mark,n, 0);
	array_fill(dist,n, inf);

	for(i=0; i<n; i++) {
		dist[i] = graph[start][i];
		if(i != start && dist[i] < inf){
            path[i]=start;
        }else{
            path[i]=-1;
        }
	}

	mark[start]=1;
	clock_t begin_clock = clock();
	while(1) {
		min = inf;
        v = -1;
		//Encontrar la distancia más pequeña
		for(i = 0; i < n; i++) {
			if(!mark[i]) {
				if(dist[i] < min){
                    min = dist[i];
                    v = i;
                }
			}
		}
		if(v==-1)break; //Ya no hay ruta más corta
		//Actualizamos la distancia más corta
		mark[v]=1;
		for(i = 0; i < n; i++) {
			if(!mark[i] && graph[v][i]!=inf && dist[v]+graph[v][i]<dist[i]) {
				dist[i] = dist[v] + graph[v][i];
				path[i] = v;
			}
		}
	}

	clock_t end_clock = clock();
	double time_spent = (double)(end_clock - begin_clock) / CLOCKS_PER_SEC;

	//Printing the output path
	printf("Starting node | End node | Source distance | Corresponding path |\n");
	for(i = 0; i < n; i++) {
		if(i==start) continue;
		array_fill(shortest,n, 0);
		printf("      %d       |",start);
		printf("     %d    |",i);
		printf("        %d        | ",dist[i]);
		int k=0;
		shortest[k]=i;
		while(path[shortest[k]] != start) {
			k++;
			shortest[k] = path[shortest[k-1]];
		}
		k++;
		shortest[k] = start;
		for(j = k; j > 0; j--) {
			printf("%d->",shortest[j]);
		}
		printf("%d\n",shortest[0]);
	}

	printf("Time elapsed: %f ms\n", time_spent);
	
	free(path);
	free(shortest);
	free(mark);
	return ;
}

int readmatrix(size_t size, int (*a)[size], const char* filename) {
    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL){ return 0; }
    
	//Lectura del archivo donde lee puros enteros
    for(size_t i = 0; i < size; ++i) {
        for(size_t j = 0; j < size; ++j){ fscanf(pf, "%d", a[i] + j); }
    }
    fclose (pf);
    
	//Asignamos los valores 0 a nuestra representación de infinito
	//excepto los de la diagonal
    for(size_t i= 0; i < size; i++){
        for(size_t j= 0; j < size; j++){
            if(a[i][j] == 0 && i != j){
                a[i][j] = inf;
            }
        }
    }
    return 1;
}

int main() {
	int dist[V_SIZE];
	
    int W[V_SIZE][V_SIZE];
    readmatrix(V_SIZE, W, NAME_FILE);
    
	//Printing the matrix to see the representation of the graph
    //for(size_t i = 0; i < V_SIZE; ++i) { for(size_t j = 0; j < V_SIZE; ++j){ printf("[%7d]", W[i][j]); } puts(""); }
    
	//Do dijkstra in the graph W from 0 node
    dijkstra(W, V_SIZE, STARTING_NODE, dist);
    return 0;
}
