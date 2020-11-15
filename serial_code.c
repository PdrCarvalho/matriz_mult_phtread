#include <stdio.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

main(int argc, char const *argv[])
{

    //Definição de variaveis
    time_t start_process = time(NULL);
    int i, j,  x;

    //Entrada de dados
    long int linhaA = atol(argv[1]);
    srand(10);
    //int **matrizA = (int **)malloc(linhaA * sizeof(int*));
/*     int (*matrizA)[linhaA];
    int (*matrizB)[linhaA];
    int (*matrizC)[linhaA];
    matrizA = (int (*)[linhaA])malloc(sizeof(*matrizA)*linhaA);
    matrizB = (int (*)[linhaA])malloc(sizeof(*matrizB)*linhaA);
    matrizC = (int (*)[linhaA])malloc(sizeof(*matrizC)*linhaA); */
    int **matrizB = (int **)malloc(linhaA * sizeof(int*));
    int **matrizC = (int **)malloc(linhaA * sizeof(int*));
    int **matrizA = (int **)malloc(linhaA * sizeof(int*));
    for(int i = 0; i < linhaA; i++){
         matrizB[i] = (int *)malloc(linhaA * sizeof(int));
         matrizA[i] = (int *)malloc(linhaA * sizeof(int));
         matrizC[i] = (int *)malloc(linhaA * sizeof(int));
         }

    float  aux = 0;

    for (i = 0; i < linhaA; i++)
    {
        for (j = 0; j < linhaA; j++)
        {
            matrizA[i][j] = rand() % 100;
            matrizB[i][j] = rand() % 100;
        }
    }
    
    for (i = 0; i < linhaA; i++)
    {
        for (j = 0; j < linhaA; j++)
        {

            matrizC[i][j] = 0;
            for (x = 0; x < linhaA; x++)
            {
                aux += matrizA[i][x] * matrizB[x][j];
            }

            matrizC[i][j] = aux;
            aux = 0;
        }
    }

    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "serial_time.txt";
    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "%ld,%ld,\n", linhaA, (end_process - start_process));
    fclose(fp);
    /* // Imprime as matrizes definidas
    printf("---------------------------- 1 - Matriz Gerada ---------------------------------\n\n");

    for (i = 0; i < linhaA; i++)
    {
        for (j = 0; j < linhaA; j++)
        {
            printf("%d ", matrizA[i][j]);
        }
        printf("\n\n");
    }

    printf("---------------------------- 2 - Matriz Gerada ---------------------------------\n\n");
    for (i = 0; i < linhaA; i++)
    {
        for (j = 0; j < linhaA; j++)
        {
            printf("%d ", matrizB[i][j]);
        }
        printf("\n\n");
    }

    printf("---------------------------- 3 - Matriz Gerada ---------------------------------\n\n");

    //Processamento e saida em tela  =  PRODUTO DAS MATRIZES
    for (i = 0; i < linhaA; i++)
    {
        for (j = 0; j < linhaA; j++)
        {
            printf("%d ", matrizC[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n"); */
    free(matrizA);
    free(matrizB);
    free(matrizC);
    return 0 ;
}