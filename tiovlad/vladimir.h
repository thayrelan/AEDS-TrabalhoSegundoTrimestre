#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"


typedef struct guia{
    int peso;
    int vertice;
}guiaStruct;


void Insere(int ** caminho, int qnt_vertices);
guiaStruct MenorAresta(int **vertice, int*visitados, int qnt_vertices, int ind);
void MenorCaminho(int qnt_vertices, int ** sistema_rodoviario, int**caminho, int*visitados, int origem);
void GrafoTeste(int qnt_vertices, int**sistema_rodoviario);
void FotoVladimir();