#ifndef ALGORITMOS
#define ALGORITMOS

#include "grafo.h"

// Estrutura para representar uma aresta ordenada por peso
typedef struct {
    int origem, destino, peso;
} ArestaOrdenada;

// Estrutura para a união e busca
typedef struct {
    int *pai, *rank;
    int numVertices;
} Conjunto;

// Implementação de uma fila simples
typedef struct {
    int *dados;
    int frente, tras, capacidade;
} Fila;

// Estrutura auxiliar para armazenar os caminhos
typedef struct {
    int distancia;
    int predecessor;
} Caminho;


// -------------------------------------
// -- Funções da fila --

// Cria e inicializa uma fila com a capacidade especificada.
// entradas: 
//   - capacidade: número máximo de elementos que a fila pode armazenar.
// saídas: 
//   - Retorna um ponteiro para a estrutura de fila criada.
Fila* criarFila(int capacidade);

// Verifica se a fila está vazia.
// entradas: 
//   - fila: ponteiro para a estrutura da fila.
// saídas: 
//   - Retorna 1 se a fila estiver vazia, 0 caso contrário.
int filaVazia(Fila* fila);

// Insere um elemento no final da fila.
// entradas: 
//   - fila: ponteiro para a estrutura da fila.
//   - valor: elemento a ser inserido na fila.
// saídas: 
//   - Nenhuma (a fila é modificada diretamente).
void enfileirar(Fila* fila, int valor);

// Remove e retorna o elemento na frente da fila.
// entradas: 
//   - fila: ponteiro para a estrutura da fila.
// saídas: 
//   - Retorna o elemento removido da fila.
int desenfileirar(Fila* fila);

// Libera a memória alocada para a fila.
// entradas: 
//   - fila: ponteiro para a estrutura da fila a ser liberada.
// saídas: 
//   - Nenhuma (a memória é liberada diretamente).
void liberarFila(Fila* fila);


// -------------------------------------
// -- Funções do DFS --

// Executa a busca em profundidade (DFS) de forma recursiva a partir de um vértice.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - vertice: índice do vértice atual na busca.
//   - visitado: vetor que armazena se um vértice já foi visitado.
// saídas: 
//   - Nenhuma (os vértices são visitados e impressos durante a execução).
void dfsRecursivo(Grafo* grafo, int vertice, int* visitado);

// Executa a busca em profundidade (DFS) a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de início da busca.
// saídas: 
//   - Nenhuma (os vértices visitados são impressos na tela).
void buscaProfundidade(Grafo* grafo, int origem);


// -------------------------------------
// -- Funções do BFS --

// Executa a busca em largura (BFS) a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de início da busca.
// saídas: 
//   - Nenhuma (os vértices visitados são impressos na tela).
void buscaLargura(Grafo* grafo, int origem);


// -------------------------------------
// -- Funções do Bellman-Ford --

void inicializarCaminhos(Caminho* caminhos, int numVertices, int origem);
void imprimirCaminho(Caminho* caminhos, int destino);
void bellmanFord(Grafo* grafo, int origem);


// -------------------------------------
// -- Funções do conjunto união-busca --

// Cria e inicializa um conjunto para a estrutura união-busca (disjoint-set).
// entradas: 
//   - numVertices: número total de vértices no conjunto.
// saídas: 
//   - Retorna um ponteiro para a estrutura de conjunto inicializada.
Conjunto* criarConjunto(int numVertices);

// Encontra o representante (raiz) do conjunto ao qual um vértice pertence, aplicando compressão de caminho.
// entradas: 
//   - conjunto: ponteiro para a estrutura do conjunto união-busca.
//   - vertice: índice do vértice a ser encontrado.
// saídas: 
//   - Retorna o representante (raiz) do conjunto do vértice.
int encontrar(Conjunto* conjunto, int vertice);

// Une dois conjuntos disjuntos, aplicando a técnica de união por rank.
// entradas: 
//   - conjunto: ponteiro para a estrutura do conjunto união-busca.
//   - raiz1: representante do primeiro conjunto.
//   - raiz2: representante do segundo conjunto.
// saídas: 
//   - Nenhuma (modifica a estrutura do conjunto unindo os elementos).
void unir(Conjunto* conjunto, int raiz1, int raiz2);

// Libera a memória alocada para a estrutura do conjunto união-busca.
// entradas: 
//   - conjunto: ponteiro para a estrutura do conjunto a ser liberado.
// saídas: 
//   - Nenhuma (memória desalocada).
void liberarConjunto(Conjunto* conjunto);


// -------------------------------------
// -- Funções de Kruskal --

// Compara duas arestas pelo peso, utilizada na ordenação com qsort.
// entradas: 
//   - a: ponteiro para a primeira aresta.
//   - b: ponteiro para a segunda aresta.
// saídas: 
//   - Retorna um valor negativo se a primeira aresta for menor, 
//     zero se forem iguais, e um valor positivo se for maior.
int compararArestas(const void* a, const void* b);

// Implementa o algoritmo de Kruskal para encontrar a Árvore Geradora Mínima (AGM) de um grafo.
// entradas: 
//   - grafo: ponteiro para o grafo sobre o qual o algoritmo será executado.
// saídas: 
//   - Nenhuma (exibe a AGM no console e gera um arquivo DOT e PNG para visualização).
void kruskal(Grafo* grafo);

// Gera um arquivo DOT e uma imagem destacando a Árvore Geradora Mínima (AGM) encontrada pelo algoritmo de Kruskal.
// entradas: 
//   - grafo: ponteiro para o grafo original.
//   - AGM: array de arestas pertencentes à AGM.
//   - numArestas: número de arestas na AGM.
//   - nomeDOT: nome do arquivo DOT a ser gerado.
//   - nomeImagem: nome do arquivo de imagem resultante.
// saídas: 
//   - Nenhuma (gera os arquivos DOT e imagem).
void gerarImagemKruskal(Grafo* grafo, ArestaOrdenada* AGM, int numArestas, const char* nomeDOT, const char* nomeImagem);


// -------------------------------------
// -- Funções de Componentes Fortemente Conexas --

void dfsPilha(Grafo* grafo, int v, bool visitado[], int pilha[], int* topo);

void dfsComponente(Grafo* grafoT, int v, bool visitado[], int componente[], int* tamanho);

void encontrarCFC(Grafo* grafo);

void gerarImagemCFC(Grafo* grafo, const char* nomeArquivo);


#endif