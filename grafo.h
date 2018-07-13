typedef struct grafo Grafo;
Grafo* criaGrafo(int nro_vertice, int Gmax, int eh_ponderado);
void liberaGrafo( Grafo* gr);
int insereAresta( Grafo* gr, int origem, int dest, int digrafo, float peso);
int removeAresta( Grafo* gr, int origem, int dest, int digrafo);
void buscaProfundidade(Grafo* gr, int ini, int *visitado, int cont);
void buscaProfundidade_Grafo( Grafo* gr, int ini, int *visitado);