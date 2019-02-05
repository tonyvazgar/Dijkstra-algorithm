#include <stdio.h>

int readmatrix(size_t size, int (*a)[size], const char* filename)
{
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
    return 1;
}

int * hola(int size, int matrix[size][size]){
    int m[size][size];
    int i, j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(matrix[i][j] == 0 && i!=j){
                matrix[i][j] = 10000;
            }
        }
    }
    return m;
}

int main(void)
{
    int matrix[16][16];
    
    int *p;
    
    
    readmatrix(16, matrix, "matrix.txt");
    
    
    
    for(size_t i = 0; i < 16; ++i)
    {
        for(size_t j = 0; j < 16; ++j){
            printf("%d     ", matrix[i][j]);
        }
        puts("");
    }
    
    return 0;
}
