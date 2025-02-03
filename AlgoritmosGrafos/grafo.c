#include "grafo.h"

// Função para criar um novo nó na lista de adjacências
No* criarNo(int destino, int peso) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->aresta.destino = destino;
    novoNo->aresta.peso = peso;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar um grafo com um número específico de vértices
Grafo* criarGrafo(int numVertices, int orientado) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->orientado = orientado;
    grafo->listaAdj = (No**)malloc(numVertices * sizeof(No*));

    for (int i = 0; i < numVertices; i++) {
        grafo->listaAdj[i] = NULL;
    }

    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    No* novoNo = criarNo(destino, peso);

    // Inserção ordenada na lista de adjacências
    No** atual = &(grafo->listaAdj[origem]);
    while (*atual != NULL && (*atual)->aresta.destino < destino) {
        atual = &((*atual)->proximo);
    }
    novoNo->proximo = *atual;
    *atual = novoNo;

    // Se o grafo não for orientado, adicionar a aresta no sentido contrário
    if (!grafo->orientado) {
        No* novoNoInverso = criarNo(origem, peso);
        atual = &(grafo->listaAdj[destino]);
        while (*atual != NULL && (*atual)->aresta.destino < origem) {
            atual = &((*atual)->proximo);
        }
        novoNoInverso->proximo = *atual;
        *atual = novoNoInverso;
    }
}

// Função para liberar a memória alocada para o grafo
void liberarGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        No* atual = grafo->listaAdj[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(grafo->listaAdj);
    free(grafo);
}

// Função para imprimir o grafo (para debug)
void imprimirGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        No* atual = grafo->listaAdj[i];
        printf("Vértice %d:", i);
        while (atual != NULL) {
            printf(" -> %d (peso %d)", atual->aresta.destino, atual->aresta.peso);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

int main() {
    Grafo* grafo = criarGrafo(5, 1); // Grafo orientado com 5 vértices
    adicionarAresta(grafo, 0, 1, 11);
    adicionarAresta(grafo, 0, 2, -4);
    adicionarAresta(grafo, 1, 3, -5);
    adicionarAresta(grafo, 2, 4, 7);
    adicionarAresta(grafo, 3, 0, 2);
    adicionarAresta(grafo, 3, 2, 8);
    adicionarAresta(grafo, 4, 2, 19);

    imprimirGrafo(grafo);

    liberarGrafo(grafo);
    return 0;
}