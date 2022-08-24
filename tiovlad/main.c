#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"


#define TOTAL 5
#define COMECO 0
#define FIM 4
#define BOLSAS_SANGUE 100000


typedef struct guia{
    int peso;
    int vertice;
}guiaStruct;

//Inicializa o caminho como infinito
void Insere(int ** caminho, int qnt_vertices){
    int i, j;
    for(i = 0; i < qnt_vertices; i++){
        for(j = 0; j < qnt_vertices; j++){
            caminho[i][j] = BOLSAS_SANGUE;
        }
    }
}

//Descobre a menor aresta do adjacente
guiaStruct MenorAresta(int **vertice, int*visitados, int qnt_vertices, int ind){
    int i, j, contador = 0;
    guiaStruct menor, menor2;
    menor.peso = BOLSAS_SANGUE;
    
    for(i = 0; i < qnt_vertices; i++){
        if(vertice[ind][i] != 1000 && visitados[i] != 1){
            if(menor.peso > vertice[ind][i]){
                menor.peso = vertice[ind][i];
                menor.vertice = i;
            }
        }
    }
    return menor;
}

//Descobre o menor caminho
void MenorCaminho(int qnt_vertices, int ** sistema_rodoviario, int**caminho, int*visitados, int origem){
    int i, j = 0, peso = 0, keep, l;
    guiaStruct menor;
    //Cria o menor caminho entre vertices
    for(i = 0; i < qnt_vertices; i++){
        for(j = 0; j < qnt_vertices; j++){
            if(i == 0){
                //O caminho inicial é sempre igual aos adjacentes do vertice origem
                caminho[i][j] = sistema_rodoviario[origem][j];
            }
            else{
               //Determina o menor caminho entre os vertices não visitados
                if(visitados[j] != 1){
                //Determina o menor caminho somente si, houver conexão 
                if(sistema_rodoviario[origem][j]!=BOLSAS_SANGUE){
                    //Determina se o menor caminho é o pré-existente ou o novo
                    if(sistema_rodoviario[origem][j]+peso < caminho[i-1][j]){
                        caminho[i][j] = sistema_rodoviario[origem][j] +peso;
                    }
                    else{
                        caminho[i][j] = caminho[i-1][j];
                    }
                }
                //Determina o caminho pré-existente como o menor caminho
                else{
                    caminho[i][j] = caminho[i-1][j];    
                }
               }
               //Determina o caminho pré-existente como o menor caminho
               else{
                caminho[i][j] = caminho[i-1][j];
               }
               //Marca o vertice como visitado
               visitados[origem] = 1;
            }
        }
        //Determina o próximo vertice a ter seus adjacentes visitados
        menor = MenorAresta(caminho, visitados, qnt_vertices, i);
        peso = menor.peso;
        if(peso >= 12 && peso <24){
            peso = 24;
        }
        else if(peso >= 24){
            keep = peso%24;
            l = peso/24;
            if(keep >= 12){
                peso = 24*l+24; 
            }
            else{
                peso = 24*l+keep;
            }
        }
        origem = menor.vertice;      
    }
}

//Função em andamento
void ImprimePercurso(int destino, int origem, int**sistema_rodoviario, int**caminho, int qnt_vertices){
    int i, j=0, dist, dif, keep;
    int *temp =(int *)calloc(qnt_vertices, sizeof(int));
    keep = destino;
    if(caminho[destino][destino] == BOLSAS_SANGUE){
        printf("Nao eh possivel alcancar esse vertice\n");
    }
    //Vai do destino até chegar a origem
    else if(sistema_rodoviario[destino][origem] == caminho[destino][destino]){
        printf("%d-->%d\n", origem+1, destino+1);
    }
    else{
        while(destino != origem){
            if(sistema_rodoviario[destino][origem] == caminho[destino][destino]){
                printf("%d-->", origem+1);
                break;
            }
            //printf("here\n");
             //Proucura nos adjacentes qual o correto
            for(i = 0; i < qnt_vertices; i++){
                 //Estabelece se há conexão entre o vértice destino e o vértice i
                if(sistema_rodoviario[destino][i] != BOLSAS_SANGUE){
                     dist = sistema_rodoviario[destino][i];    
                     if(dist>=12){
                         dist = dist+24;
                     }
                     dif = caminho[destino][destino]-caminho[i][i];
                     printf("%d\n", caminho[i][i]);
                     
                     //Verifica se o vértice i, é parte do percurso do menor caminho
                    if(dist == dif){
                        temp[j] = i;
                        j++;
                        destino = i;
                        break;
                    }
                }
            }     
        }
        for(i = 1; i <= j; i++){
          printf("%d-->", temp[j-i]+1);
        }
        printf("%d\n", keep+1);
    }
    free(temp);
}

//Grafo usado para testes; 
void GrafoTeste(int qnt_vertices, int**sistema_rodoviario){
    for(int i = 0; i < qnt_vertices; i++){
        for(int j = 0; j < qnt_vertices; j++){
            if(i == j){
                sistema_rodoviario[i][j] = 0;
            }
            else{
                sistema_rodoviario[i][j] = BOLSAS_SANGUE;
            }
        }
    }
    sistema_rodoviario[0][1] = 12;
    sistema_rodoviario[0][2] = 8;
    sistema_rodoviario[1][0] = 12;
    sistema_rodoviario[2][0] = 8;
    sistema_rodoviario[1][3] = 1;
    sistema_rodoviario[2][3] = 8;
    sistema_rodoviario[3][2] = 8;
    sistema_rodoviario[3][1] = 1;

    sistema_rodoviario[1][4] = 3;
    sistema_rodoviario[4][1] = 3;
    sistema_rodoviario[3][4] = 8;
    sistema_rodoviario[4][3] = 8;

    
   
}


//main
int main(int argc, char *argv[]){

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

    printf("3x4 DO VLADIMIR: \n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠟⠛⠛⠛⠛⠛⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⡿⠋⣡⣤⣶⣶⣶⣶⣆⣰⣶⣶⣶⣶⣤⣌⠛⢿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⠁⠈⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠁⠈⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⡿⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⢿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⡇⠀⣿⡿⠋⠉⠉⠙⠻⠿⠿⠟⠋⠉⠉⠙⢿⣿⠀⢸⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⡟⠻⢿⣴⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣦⡿⠟⢻⣿⣿⣿\n");
    printf("⣿⣿⣿⣷⠀⠀⣿⠁⢀⣴⣷⣄⠀⠀⠀⠀⠀⠀⣠⣾⣦⡀⠈⣿⠀⠀⣾⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⡀⠀⣿⠀⠙⢋⣤⣿⣷⣄⠀⠀⣠⣾⣿⣤⡙⠋⠀⣿⠀⢀⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣷⣄⣿⠀⠰⠿⠇⠀⠿⠿⠁⠈⠿⠿⠀⠸⠿⠆⠀⣿⣠⣾⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⡿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⢿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⡿⠟⠋⠁⠀⠈⠻⣦⠀⠀⠀⠻⢶⡶⠟⠀⠀⠀⣴⠟⠁⠀⠈⠙⠻⢿⣿⣿\n");
    printf("⣿⣷⣦⣄⡀⠀⠀⠀⠀⣿⠀⣤⣀⣀⣀⣀⣀⣀⣤⠀⣿⠀⠀⠀⠀⢀⣠⣴⣾⣿\n");
    printf("⣿⣿⣿⣿⣿⣦⡀⠀⠀⣿⠀⠈⢻⡟⠛⠛⢻⡟⠁⠀⣿⠀⠀⢀⣴⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣆⠀⢻⣤⣀⡀⠁⠀⠀⠈⠀⣀⣤⡟⠀⣰⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣤⣤⣬⣭⣿⣿⣿⣿⣿⣿⣭⣥⣤⣤⣿⣿⣿⣿⣿⣿⣿⣿\n\n");
    

    //Inicializa & Cria variáveis que serão usadas no decorrer do programa
    Insere(caminho, qnt_vertices);
    sistema_rodoviario = gp_creates(qnt_vertices, qnt_vertices);
    //GrafoTeste(qnt_vertices, sistema_rodoviario);
    gp_build(sistema_rodoviario, qnt_vertices);
    convert(sistema_rodoviario, qnt_vertices, -1, origem, destino, 2);
    //GrafoTeste(qnt_vertices, sistema_rodoviario);
    gp_print(sistema_rodoviario, qnt_vertices, qnt_vertices);
    printf("\n");
    
    keep = origem;    

    for(i = 0; i < qnt_vertices; i++){
        if(sistema_rodoviario[0][i] == BOLSAS_SANGUE){
            j++;
        }
    }
    
    if(j == qnt_vertices){
        printf("Ao que parece vladimir mora em um local onde nao hah um sistema rodoviario\n");
    }else{
        //Descobre o menor caminho de um ponto ao outro
        MenorCaminho(qnt_vertices, sistema_rodoviario, caminho, visitados, origem);
        gp_print(caminho, qnt_vertices, qnt_vertices);
        printf("\n");
    
        //imprime o menor percursso
        //ImprimePercurso(destino, origem, sistema_rodoviario, caminho, qnt_vertices);    
        printf("\n");    
    }
    caminho[destino][destino] = caminho[destino][destino]-18;
    keep++;
    if(caminho[destino][destino]>24){
        keep = caminho[destino][destino]/24 + keep;
    }
    if(keep == 4166){
        printf("vladimir é pobre, a cidade dele não tem sistema rodoviario\n");    
    }
    else{
        printf("vladimir gastaria %d litros de sangue\n", keep);
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