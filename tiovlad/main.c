#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "grafo.h"
#include "vladimir.h"

#define TOTAL 8
#define COMECO 0
#define FIM 5


//main
int main(int argc, char *argv[]){

    char matrix[10][12];
                strcpy(matrix[0],  "    )_(   ");                                         
                strcpy(matrix[1],  "    | |   ");                     
                strcpy(matrix[2],  "  .-'-'-. ");     
                strcpy(matrix[3],  " /-::_..- ");    
                strcpy(matrix[4],  " )_     _(");   
                strcpy(matrix[5],  " |;::    |");   
                strcpy(matrix[6],  " |;::    |");   
                strcpy(matrix[7],  " |;::    |");   
                strcpy(matrix[8],  " |;::-.._|");   
                strcpy(matrix[9],  " `-.._..-'");  


    //variáveis absolutas(raramente tem seu valor alterado)
    int qnt_vertices = TOTAL, origem = COMECO, destino = FIM, keep = 0;
    int ** sistema_rodoviario;

    //variáveis temporárias(constantemente tem seu valor alterado)
    int i, j = 0, peso, dif, dist;
    int *visitados = (int*)calloc(qnt_vertices, sizeof(int));
    int ** caminho = (int**)malloc(sizeof(int*)*qnt_vertices);
    guiaStruct menor; 

    ///Alocação//
    for(i = 0; i < qnt_vertices; i++){
        caminho[i] = (int*) calloc (qnt_vertices, sizeof(int));
    }
    FotoVladimir();
        



    //Inicializa & Cria variáveis que serão usadas no decorrer do programa
    Insere(caminho, qnt_vertices);
    sistema_rodoviario = GrafoCria(qnt_vertices, qnt_vertices);
    GrafoConstroi(sistema_rodoviario, qnt_vertices);
    Converte(sistema_rodoviario, qnt_vertices, -1, origem, destino, 2);
    //GrafoTeste(qnt_vertices, sistema_rodoviario);


    //Imprime Grafo Contruído
    printf("+---------------------------------------------------------------------+\n");
    printf("|                               GRAFO                                 |\n");
    printf("+---------------------------------------------------------------------+\n");    
    GrafoImprime(sistema_rodoviario, qnt_vertices, qnt_vertices);
    printf("+---------------------------------------------------------------------+\n");  
    printf("\n\n");
    
    /*Verifica se não há nenhuma conexão da cidade origem para qualquer outra*/
    keep = origem;    
    for(i = 0; i < qnt_vertices; i++){
        if(sistema_rodoviario[0][i] == LIMITE){
            j++;
        }
    }
    if(j == qnt_vertices){
        printf("Ao que parece vladimir mora em um local onde nao hah um sistema rodoviario\n");
    }else{
        //Descobre o menor caminho de um ponto ao outro
        MenorCaminho(qnt_vertices, sistema_rodoviario, caminho, visitados, origem);
        printf("+---------------------------------------------------------------------+\n");
        printf("|                            DJIKSTRA                                 |\n");
        printf("+---------------------------------------------------------------------+\n"); 
        GrafoImprime(caminho, qnt_vertices, qnt_vertices);
        printf("+---------------------------------------------------------------------+\n"); 
        printf("\n");
    }


    if(j != qnt_vertices){  
        caminho[qnt_vertices-1][destino] = caminho[qnt_vertices-1][destino]-18;
        keep++;
        if(caminho[qnt_vertices-1][destino]>24){
             keep = caminho[qnt_vertices-1][destino]/24 + keep;
        }
        if(keep == 4166){
          printf("A CIDADE DESTINO NAO PODE SER ALCANCADA (SADGE)\n");    
        }
        else{
            printf("VLADIMIR GASTARIA %d LITROS DE SANGUE\n", keep);
            j = keep;
            for(i = 0; i<10;i++){          
                keep =j;         
                for(keep; keep>0; keep--){
                    printf("%s  ", matrix[i]);
                }
                printf("\n");
            }
        }
    }
    
    
    //Liberação de memória
    free(visitados);
    for(i = 0; i < qnt_vertices; i++){
        free(sistema_rodoviario[i]);
        free(caminho[i]);
    }
    free(sistema_rodoviario);
    free(caminho);

    return 0;
}