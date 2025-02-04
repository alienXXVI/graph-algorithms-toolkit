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
        printf("Vertice %d:", i);
        while (atual != NULL) {
            printf(" -> %d (peso %d)", atual->aresta.destino, atual->aresta.peso);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

// Função para carregar o grafo a partir de um arquivo de texto
Grafo* carregarGrafo(const char* caminhoArquivo) {
    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Ler a primeira linha para verificar se o grafo é orientado
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);
    int orientado = (strstr(linha, "orientado=sim") != NULL) ? 1 : 0;

    // Ler a segunda linha para obter o número de vértices
    fgets(linha, sizeof(linha), arquivo);
    int numVertices;
    sscanf(linha, "V=%d", &numVertices);

    // Criar o grafo
    Grafo* grafo = criarGrafo(numVertices, orientado);

    // Ler as arestas
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int origem, destino, peso;
        if (sscanf(linha, "(%d,%d):%d", &origem, &destino, &peso) == 3) {
            adicionarAresta(grafo, origem, destino, peso);
        } else {
            printf("Formato de aresta invalido: %s\n", linha);
        }
    }

    fclose(arquivo);
    return grafo;
}