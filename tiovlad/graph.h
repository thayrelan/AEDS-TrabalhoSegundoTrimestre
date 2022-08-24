#define FALSE 1
#define TRUE 0
#define BOLSAS_SANGUE 100000

typedef struct struct_t{

    int Distance;
    int Prior;
    int Color; 

}control;

int ** gp_creates(int vertex_qnt, int conexao_max);
void gp_print(int ** grafo, int vertex_qnt, int conexao_max);
void convert(int **grafo, int vertex_qnt, int fator_previne, int origem, int destino, int cofator);
void gp_build(int **grafo, int vertex_qnt);
void print_path(control * busca, int vertex_qnt);
void print_percurss(control * busca, int vertex_qnt, int inicio, int fim);