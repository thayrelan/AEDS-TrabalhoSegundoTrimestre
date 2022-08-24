#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "graph.h"

int ** gp_creates(int vertex_qnt, int conexao_max){

    int ** grafo = (int **) malloc (sizeof(int*) * vertex_qnt);
    for(int i = 0; i < conexao_max; i++){
        grafo[i] = (int *) calloc (conexao_max, sizeof(int));
    }
    return grafo; 
}

void gp_print(int ** grafo, int vertex_qnt, int conexao_max){
    int i;
    printf("   ");
    for(i = 0; i < vertex_qnt; i++){
        printf("     [%d]", i);
    } 
    printf("\n");
    for(i = 0; i < vertex_qnt; i++){
        printf("[%d] ", i);
        for(int j = 0; j < conexao_max; j++){
            printf("%6d  ", grafo[i][j]);
        }
        printf("\n");
    }
}

void convert(int **grafo, int vertex_qnt, int fator_previne, int origem, int destino, int cofator){
    int i, j;
    for(i = 0; i < vertex_qnt; i++){
        for(j = 0; j < vertex_qnt; j++){
            
            if(grafo[i][j] == -1){
                
                grafo[i][j] = 1;
            }
            else if(grafo[i][j] == -2){
                grafo[i][j] = BOLSAS_SANGUE;
            }
            if(i == j){
                grafo[i][j] = BOLSAS_SANGUE;
            }
        }
        
    }
    if(fator_previne == -1){
        for(j = 0; j < cofator; j++){
            grafo[j][destino] = BOLSAS_SANGUE;
            grafo[j][destino] = BOLSAS_SANGUE;
        }
    }
}

void gp_build(int **grafo, int vertex_qnt){
    int i, j;
    int connections, temp, maior=vertex_qnt*30, menor=vertex_qnt*15;  
    srand(time(NULL));
    for(i = 0; i < vertex_qnt; i++){
        
        for(j = 0; j < vertex_qnt; j++){
            
            connections = rand() % (5 - 1 + 1) + 1;
            temp = rand() % (maior - menor + menor) + menor;
            
         
            if(grafo[i][j] == -1 || grafo[i][j] == -2){
                if(grafo[i][j] == -1){
                    grafo[i][j] == 1;
                }else if(grafo[i][j] == -2){
                    grafo[i][j] == 0;
                }
            }
            else if(connections != 1){
                grafo[i][j] = temp;
                grafo[j][i] = temp; 
            }else{
                grafo[i][j] = BOLSAS_SANGUE;
                grafo[j][i] = -2;
            }
        }
        maior = maior -30;
        menor = menor -15;
    }
    
}

void printf_path(control * busca, int vertex_qnt){
    int i; 
    for(i=0;i<vertex_qnt;i++){
        if(busca[i].Distance == -5){
            printf("distancia: [N]  Prior: [N]  Color: [0]\n");
        }
        else if(busca[i].Distance == -3){
            printf("distancia: [F]  Prior: [F]  Color: [2]\n");
        }
        else{
            printf("distancia: [%d]  Prior: [%d]  Color: [%d]\n", busca[i].Distance, busca[i].Prior, busca[i].Color);
        }
    }
}

void print_percurss(control * busca, int vertex_qnt, int inicio, int fim){
    int i = fim, j = 0; 
    int temp = 0, *path;
    if(busca[fim].Color != 0){
        while(i != inicio){
            i = busca[i].Prior;
            temp++;
        }        
    }
    path = (int *)malloc(sizeof(int)*temp);
    i = fim;
    if(busca[fim].Color == 0){
        printf("vertice nao alcacahvel\n");
    }
    else{
        while(i != inicio){
            path[j] = i;
            i = busca[i].Prior;
            j++;
            
        }
        path[temp] = inicio;
        for(i = 0; i <= temp; i++){
            if(i == temp){
                printf("%d", path[temp-i]);    
            }
            else{
                printf("%d-->", path[temp-i]);
            }
        }
        printf("\n");
    }
    free(path);
}