#ifndef GRAFO
#define GRAFO

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



#endif