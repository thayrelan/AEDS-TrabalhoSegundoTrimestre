#include <stdlib.h>
#include <stdio.h>
#include "vladimir.h"
#include <string.h>

//Inicializa o caminho como infinito
void Insere(int ** caminho, int qnt_vertices){
    int i, j;
    for(i = 0; i < qnt_vertices; i++){
        for(j = 0; j < qnt_vertices; j++){
            caminho[i][j] = LIMITE;
        }
    }
}

//Descobre a menor aresta dos adjacente do vértice de indice ind
guiaStruct MenorAresta(int **vertice, int*visitados, int qnt_vertices, int ind){
    int i, j, contador = 0;
    guiaStruct menor, menor2;
    menor.peso = LIMITE;
    
    for(i = 0; i < qnt_vertices; i++){
        //Verifica somente os vértices com conexão não visitados
        if(vertice[ind][i] != LIMITE && visitados[i] != 1){
            //Se a aresta do vértice adjacente ao vertice ind for menor do que o pré estabelecido
            //menor se torna esse adjacente
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
                if(sistema_rodoviario[origem][j]!=LIMITE){
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

        //Se o peso real do vértice alcancado for maior que 12, isso significa que vladimir terá de esperar
        //na estação
        /*if(peso >= 12 && peso <24){
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
        }*/
        origem = menor.vertice;      
    }
}


//Grafo estático usado para testes; 
void GrafoTeste(int qnt_vertices, int**sistema_rodoviario){
    for(int i = 0; i < qnt_vertices; i++){
        for(int j = 0; j < qnt_vertices; j++){
            if(i == j){
                sistema_rodoviario[i][j] = 0;
            }
            else{
                sistema_rodoviario[i][j] = LIMITE;
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

}

//Rosto do Vladimir
void FotoVladimir(){
    printf("\e[0;47;40m┠──────────────────────────────────────────────────────────────────────────────────────────────────────────────┨\033[0;0m\n");
	printf("\e[0;47;40m┃                                                                                                              ┃\033[0;0m\n");
    printf("\e[0;47;40m┃                                  \e[0;36;40m          !!!!3X4 DO TIO VLAD!!!\e[0;47;40m                                            ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                                                                                              ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠟⠛⠛⠛⠛⠛⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣿⡿⠋⣡⣤⣶⣶⣶⣶⣆⣰⣶⣶⣶⣶⣤⣌⠛⢿⣿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣿⠁⠈⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠁⠈⣿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⡿⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⢿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⡇⠀⣿⡿⠋⠉⠉⠙⠻⠿⠿⠟⠋⠉⠉⠙⢿⣿⠀⢸⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⡟⠻⢿⣴⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣦⡿⠟⢻⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣷⠀⠀⣿⠁⢀⣴⣷⣄⠀⠀⠀⠀⠀⠀⣠⣾⣦⡀⠈⣿⠀⠀⣾⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⡀⠀⣿⠀⠙⢋⣤⣿⣷⣄⠀⠀⣠⣾⣿⣤⡙⠋⠀⣿⠀⢀⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣷⣄⣿⠀⠰⠿⠇⠀⠿⠿⠁⠈⠿⠿⠀⠸⠿⠆⠀⣿⣠⣾⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣿⡿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⢿⣿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣿⡿⠟⠋⠁⠀⠈⠻⣦⠀⠀⠀⠻⢶⡶⠟⠀⠀⠀⣴⠟⠁⠀⠈⠙⠻⢿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                        ⣿⣷⣦⣄⡀⠀⠀⠀⠀⣿⠀⣤⣀⣀⣀⣀⣀⣀⣤⠀⣿⠀⠀⠀⠀⢀⣠⣴⣾⣿                                        ┃\033[0;0m\n");
    printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣦⡀⠀⠀⣿⠀⠈⢻⡟⠛⠛⢻⡟⠁⠀⣿⠀⠀⢀⣴⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
    printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣿⣿⣆⠀⢻⣤⣀⡀⠁⠀⠀⠈⠀⣀⣤⡟⠀⣰⣿⣿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
    printf("\e[0;47;40m┃                                        ⣿⣿⣿⣿⣿⣿⣿⣿⣤⣤⣬⣭⣿⣿⣿⣿⣿⣿⣭⣥⣤⣤⣿⣿⣿⣿⣿⣿⣿⣿                                        ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                                                                                              ┃\033[0;0m\n");
	printf("\e[0;47;40m┃                                                                                                              ┃\033[0;0m\n");
	printf("\e[0;47;40m┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0;0m\n");
    printf("\n\n");
}

