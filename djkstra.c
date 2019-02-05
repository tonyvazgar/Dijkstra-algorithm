#include <stdio.h>
#include <stdlib.h>

//Representing infinity
#define inf 	100000
//Number of nodes
#define V_SIZE	64

//Array fill
void array_fill(int * array, int len, int val) {
	int i;
	for (i = 0; i < len; i++) { array[i] = val; }
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
	while(1) {
		min = inf;
        v = -1;
		//Encontrar la distancia más pequeña
		for(i = 0; i < n; i++) {
			if(!mark[i]) {
				if(dist[i]<min){
                    min=dist[i];
                    v=i;
                }
			}
		}
		if(v==-1)break; //Ya no hay ruta más corta
		//Actualizamos la distancia más corta
		mark[v]=1;
		for(i = 0; i < n; i++) {
			if(!mark[i] &&
					graph[v][i]!=inf&&
					dist[v]+graph[v][i]<dist[i]) {
				dist[i]=dist[v]+graph[v][i];
				path[i]=v;
			}
		}
	}
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
		while(path[shortest[k]]!=start) {
			k++;shortest[k]=path[shortest[k-1]];
		}
		k++;shortest[k]=start;
		for(j=k;j>0;j--) {
			printf("%d->",shortest[j]);
		}
		printf("%d\n",shortest[0]);
	}
	free(path);
	free(shortest);
	free(mark);
	return ;
}


int readmatrix(size_t size, int (*a)[size], const char* filename) {
    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL){
        return 0;
    }
    
    for(size_t i = 0; i < size; ++i) {
        for(size_t j = 0; j < size; ++j){
            fscanf(pf, "%d", a[i] + j);
        }
    }
    fclose (pf);
    
    for(size_t i= 0; i < size; i++){
        for(size_t j= 0; j < size; j++){
            if(a[i][j] == 0 && i != j){
                a[i][j] = inf;
            }
        }
    }
    return 1;
}


int main()
{
	int dist[V_SIZE];
	/*int W[V_SIZE][V_SIZE] = {
				{  0,   1,   4,  inf,  inf,  inf },
				{  1,   0,   2,   7,    5,  inf },
				{  4,   2,   0,  inf,    1,  inf },
				{ inf,  7,  inf,   0,    3,    2 },
				{ inf,  5,    1,   3,   0,    6 },
				{ inf, inf,  inf,   2,   6,    0 } };
    */
    
    int W[V_SIZE][V_SIZE];
    readmatrix(64, W, "matrix64.txt");
    
    
    
    /*int W[V_SIZE][V_SIZE] = {
        {  0,  inf,  inf,  inf,  inf,  inf,  inf,  38,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf },
        { inf,   0,  inf,  inf,   65,  inf,   64,  inf,   6,  inf,  inf,  inf,  inf,  inf,  inf,  inf },
        { inf,  inf,  0,  inf,  inf,  inf,  inf,  inf,  inf,  inf,   6,   8,  inf,  inf,  inf,  62 },
        { inf,  inf,  inf, 0,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf },
        { inf, 65,  inf,  inf, 0,  inf,  inf,  inf,  inf, 6,  inf,  inf,  inf,  inf, 55,  inf },
        { inf,  inf,  inf,  inf,  inf, 0,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf,  inf },
        { inf, 64,  inf,  inf,  inf,  inf, 0, 53,  inf,  inf, 36,  inf, 45,  inf,  inf,  inf },
        {  38,  inf,  inf,  inf,  inf,  inf, 53, 0,  inf,  inf,  inf, 91,  inf, 29,  inf,  inf },
        { inf, 6,  inf,  inf,  inf,  inf,  inf,  inf, 0,  inf,  inf, 95, 55,  inf,  inf,  inf },
        { inf,  inf,  inf,  inf, 6,  inf,  inf,  inf,  inf, 0,  inf,  inf,  inf,  inf,  inf,  inf },
        { inf,  inf, 6,  inf,  inf,  inf, 36,  inf,  inf,  inf, 0,  inf,  inf,  inf,  inf,  inf },
        { inf, 0 8 0 0 0 0 91 95 0 0 0 60 0 0 0},
        { inf, 0 0 0 0 0 45 0 55 0 0 60 0 0 0 0},
        { inf, 0 0 0 0 0 0 29 0 0 0 0 0 0 0 0},
        { inf, 0 0 0 55 0 0 0 0 0 0 0 0 0 0 0},
        { inf, 0 62 0 0 0 0 0 0 0 0 0 0 0 0 0}};*/
    
    for(size_t i = 0; i < 64; ++i)
    {
        for(size_t j = 0; j < 64; ++j){
            printf("%9d", W[i][j]);
        }
        puts("");
    }
    
    dijkstra(W, V_SIZE, 0, dist);
    return 0;
}
