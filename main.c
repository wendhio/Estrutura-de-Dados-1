#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafo.h"

struct grafo{
    int eh_ponderado;   // grafo ponderado ou não
    int nro_vertice;    // número de vértices que o grafo terá
    int Gmax;           // número de arestas com a quais um vértice poderá se conectar
    int **arestas;      // alocação da matriz de arestas do grafo
    float **pesos;      // alocação da matriz de pesos das arestas
    int *grau;          // vetor para armazenar o número de arestas já associadas a um vértice.
};

Grafo* criaGrafo(int nro_vertice, int Gmax, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if( gr != NULL){
        gr->nro_vertice = nro_vertice;
        gr->Gmax = Gmax;
        gr->eh_ponderado = (eh_ponderado != 0)? 1 : 0;
        gr->grau = (int*)calloc(nro_vertice, sizeof(int));
        gr->arestas = (int**)malloc(nro_vertice*sizeof(int*));
        
        int i;
        for(i = 0; i < nro_vertice; i++)
            gr->arestas[i] = (int*)malloc(Gmax*sizeof(int));
        if(gr->eh_ponderado){
            gr->pesos = (float**)malloc(nro_vertice*sizeof(float*));
            for(i = 0; i < nro_vertice; i++)
                gr->pesos[i] = (float*)malloc(Gmax*sizeof(float));
        }   
    }
    return gr;
}

void liberaGrafo(Grafo* gr){
    if(gr != NULL){
        int i;  //Liberando lista de adjacencias( arestas)
        for(i = 0; i < gr->nro_vertice; i++)
            free(gr->arestas[i]);   
        free(gr->arestas);
        
        if( gr->eh_ponderado){
            for(i = 0; i < gr->nro_vertice; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int origem, int dest, int digrafo, float peso){
    //Verificando se o grafo é válido
    if(gr == NULL)
        return 0;
    if(origem < 0 || origem >= gr->nro_vertice)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertice)
        return 0;
    
    gr->arestas[origem][gr->grau[origem]] = dest;
    if(gr->eh_ponderado)
        gr->pesos[origem][gr->grau[origem]] = peso;
    gr->grau[origem]++;
    // Chamanda recursiva inveternando a ordem de ida->volta (dest, origem)
    if(digrafo == 0)
        insereAresta(gr, dest, origem,1, peso);
    
    return 1;   // sucesso
}

int removeAresta(Grafo* gr, int origem, int dest, int digrafo){
    //Verifica se o grafo é válido
    if(gr == NULL)
        return 0;
    if(origem < 0 || origem >= gr->nro_vertice)
        return 0;
    if( dest < 0 || dest >= gr->nro_vertice)
        return 0;
    
    int i = 0;  //Percorrer as arestas dos vertices até o final ou destino
    while(i < gr->grau[origem] && gr->arestas[origem][i] != dest)
        i++;
    if( i == gr->grau[origem])
        return 0;   //elemento não encontrado
    gr->grau[origem]--; //diminui a qtd de arestas do vertice origem
    //copia o ultimo elemento para a posição a ser removida
    gr->arestas[origem][i] = gr->arestas[origem][gr->grau[origem]];
    if(gr->eh_ponderado)
        gr->pesos[origem][i] = gr->pesos[origem][gr->grau[origem]];
    if(digrafo == 0)
        removeAresta(gr, dest, origem, 1);
    
    return 1;
}

void buscaProfundidade(Grafo* gr, int ini, int* visitado, int cont){
    int i;
    visitado[ini] = cont;
    for(i=0; i < gr->grau[ini]; i++){
        if(!visitado[gr->arestas[ini][i]])
            buscaProfundidade(gr, gr->arestas[ini][i], visitado, cont+1);
    }
}

void buscaProfundidade_Grafo(Grafo* gr, int ini, int* visitado){
    int i, cont = 1;
    for(i = 0; i < gr->nro_vertice; i++)
        visitado[i] = 0;
    buscaProfundidade(gr, ini, visitado, cont);
}

int main(int argc, char* argv[]) {
    int eh_digrafo = 1;
    Grafo* gr = criaGrafo(5,5, 0);
    insereAresta(gr,0,1,eh_digrafo,0);
    insereAresta(gr,1,3,eh_digrafo,0);
    insereAresta(gr,1,2,eh_digrafo,0);
    insereAresta(gr,2,4,eh_digrafo,0);
    insereAresta(gr,3,0,eh_digrafo,0);
    insereAresta(gr,3,4,eh_digrafo,0);
    insereAresta(gr,3,1,eh_digrafo,0);
    
    
    liberaGrafo(gr);
    return (EXIT_SUCCESS);
}

