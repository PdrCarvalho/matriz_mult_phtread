#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>


int thread_count;

int **matrizB ;
int **matrizC ;
int **matrizA ;
int row;
void *MultMatrix(void * rank){
    long my_rank = (long) rank;
    int i,j,x;
    int aux = 0;
    int local_m = row/(thread_count+1);
    
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m -1 ;
    printf("%d - first %d - last %d - local_m %d -\n",my_rank,my_first_row,my_last_row,local_m);
    for ( i = my_first_row; i <= my_last_row; i++)
    {
        
        for (j = 0; j < row; j++)
        {

            for (x = 0; x < row; x++)
            {
                aux += matrizA[i][x] * matrizB[x][j];
            }
            matrizC[i][j] = aux;
            aux = 0;
        }
        
    }
    return NULL;

}
void MultMatrixMain (int rank){
    long my_rank = (long) rank;
    int i,j,x;
    int aux = 0;
    int local_m = row/(thread_count+1);
    
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m -1 ;
    printf("%d - first %d - last %d - local_m %d -\n",my_rank,my_first_row,my_last_row,local_m);
    for ( i = my_first_row; i <= my_last_row; i++)
    {
        
        for (j = 0; j < row; j++)
        {

            for (x = 0; x < row; x++)
            {
                aux += matrizA[i][x] * matrizB[x][j];
            }
            matrizC[i][j] = aux;
            aux = 0;
        }
        
    }

}
int main(int argc, char* argv[]){
    time_t start_process = time(NULL);
    long thread;
    row = atol(argv[2]);
    int i,j;
    srand(10);
    matrizB = (int **)malloc(row * sizeof(int*));
    matrizC = (int **)malloc(row * sizeof(int*));
    matrizA = (int **)malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++){
         matrizB[i] = (int *)malloc(row * sizeof(int));
         matrizA[i] = (int *)malloc(row * sizeof(int));
         matrizC[i] = (int *)malloc(row * sizeof(int));
         }
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            matrizA[i][j] = rand() % 100;
            matrizB[i][j] = rand() % 100;
            matrizC[i][j] = 0;
        }
    }
    
    pthread_t* thread_handles;
    thread_count = strtol(argv[1],NULL,10);
    thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread],NULL,MultMatrix,(void*)thread);
    }
    MultMatrixMain(thread_count);
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }
    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "parallel_time.txt";
    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "%d,%ld,%d\n", row,(end_process - start_process),thread_count+1);
    fclose(fp);
    // Imprime as matrizes definidas
    printf("---------------------------- 1 - Matriz Gerada ---------------------------------\n\n");

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            printf("%d ", matrizA[i][j]);
        }
        printf("\n\n");
    }

    printf("---------------------------- 2 - Matriz Gerada ---------------------------------\n\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            printf("%d ", matrizB[i][j]);
        }
        printf("\n\n");
    }
 
    printf("---------------------------- 3 - Matriz Gerada ---------------------------------\n\n");

    //Processamento e saida em tela  =  PRODUTO DAS MATRIZES
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            printf("%d ", matrizC[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n");
    free(thread_handles);
    free(matrizA);
    free(matrizB);
    free(matrizC);
    return 0;
}

