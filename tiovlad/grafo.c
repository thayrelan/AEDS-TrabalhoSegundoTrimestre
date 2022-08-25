#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "grafo.h"

int ** GrafoCria(int vertex_qnt, int conexao_max){

    int ** grafo = (int **) malloc (sizeof(int*) * vertex_qnt);
    for(int i = 0; i < conexao_max; i++){
        grafo[i] = (int *) calloc (conexao_max, sizeof(int));
    }
    return grafo; 
}

void GrafoImprime(int ** grafo, int vertex_qnt, int conexao_max){
    int i;
    printf("|   ");
    for(i = 0; i < vertex_qnt; i++){
        printf("     [%d]", i);
    } 
    printf("  |");
    printf("\n");
    for(i = 0; i < vertex_qnt; i++){
        printf("| [%d] ", i);
        for(int j = 0; j < conexao_max; j++){
            printf("%6d  ", grafo[i][j]);
        }
        printf("|\n");
    }
}

void Converte(int **grafo, int vertex_qnt, int fator_previne, int origem, int destino, int cofator){
    int i, j;
    for(i = 0; i < vertex_qnt; i++){
        for(j = 0; j < vertex_qnt; j++){
            
            if(grafo[i][j] == -1){
                
                grafo[i][j] = 1;
            }
            else if(grafo[i][j] == -2){
                grafo[i][j] = LIMITE;
            }
            if(i == j){
                grafo[i][j] = LIMITE;
            }
        }
        
    }
    if(fator_previne == -1){
        for(j = 0; j < cofator; j++){
            grafo[j][destino] = LIMITE;
            grafo[j][destino] = LIMITE;
        }
    }
}

void GrafoConstroi(int **grafo, int vertex_qnt){
    int i, j;
    int conexoes, temp, maior=vertex_qnt*30, menor=vertex_qnt*15;  
    srand(time(NULL));
    for(i = 0; i < vertex_qnt; i++){
        
        for(j = 0; j < vertex_qnt; j++){
            
            conexoes = rand() % (5 - 1 + 1) + 1;
            temp = rand() % (maior - menor + menor) + menor;
            
         
            if(grafo[i][j] == -1 || grafo[i][j] == -2){
                if(grafo[i][j] == -1){
                    grafo[i][j] == 1;
                }else if(grafo[i][j] == -2){
                    grafo[i][j] == 0;
                }
            }
            else if(conexoes != 1){
                grafo[i][j] = temp;
                grafo[j][i] = temp; 
            }else{
                grafo[i][j] = LIMITE;
                grafo[j][i] = -2;
            }
        }
        maior = maior -30;
        menor = menor -15;
    }
    
}

