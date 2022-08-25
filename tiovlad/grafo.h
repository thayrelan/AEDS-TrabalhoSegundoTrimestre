#define LIMITE 100000


int ** GrafoCria(int vertex_qnt, int conexao_max);
void GrafoImprime(int ** grafo, int vertex_qnt, int conexao_max);
void Converte(int **grafo, int vertex_qnt, int fator_previne, int origem, int destino, int cofator);
void GrafoConstroi(int **grafo, int vertex_qnt);
