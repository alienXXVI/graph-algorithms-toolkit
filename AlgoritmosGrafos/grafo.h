#ifndef GRAFO
#define GRAFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

// Estrutura para representar uma aresta
typedef struct {
    int destino;
    int peso;
} Aresta;

// Estrutura para representar um nó da lista de adjacências
typedef struct No {
    Aresta aresta;
    struct No* proximo;
} No;

// Estrutura para representar o grafo
typedef struct {
    int numVertices;
    int orientado; // 1 para orientado, 0 para não orientado
    No** listaAdj;
} Grafo;

No* criarNo(int destino, int peso);
Grafo* criarGrafo(int numVertices, int orientado);
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso);
void liberarGrafo(Grafo* grafo);
void imprimirGrafo(Grafo* grafo);
Grafo* carregarGrafo(const char* caminhoArquivo);
void gerarDOT(Grafo* grafo, const char* nomeArquivo);

#endif