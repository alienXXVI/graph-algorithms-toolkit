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


// -------------------------------------
// -- Funções do Grafo --

// Cria um novo nó na lista de adjacências de um grafo.
// entradas: 
//   - destino: vértice de destino da aresta.
//   - peso: peso da aresta associada ao nó.
// saídas: 
//   - Retorna um ponteiro para o novo nó criado.
No* criarNo(int destino, int peso);

// Cria um grafo com um número específico de vértices, podendo ser orientado ou não.
// entradas: 
//   - numVertices: número total de vértices no grafo.
//   - orientado: indica se o grafo é orientado (1 para sim, 0 para não).
// saídas: 
//   - Retorna um ponteiro para a estrutura do grafo inicializada.
Grafo* criarGrafo(int numVertices, int orientado);

// Adiciona uma aresta ao grafo, com inserção ordenada na lista de adjacências.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de origem da aresta.
//   - destino: vértice de destino da aresta.
//   - peso: peso associado à aresta.
// saídas: 
//   - Nenhuma (modifica a estrutura do grafo adicionando a aresta).
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso);

// Libera a memória alocada para a estrutura do grafo e suas listas de adjacências.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo a ser liberado.
// saídas: 
//   - Nenhuma (memória desalocada).
void liberarGrafo(Grafo* grafo);

// Imprime a lista de adjacências do grafo, exibindo seus vértices e conexões.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo a ser impresso.
// saídas: 
//   - Nenhuma (exibe a estrutura do grafo no console).
void imprimirGrafo(Grafo* grafo);

// Carrega um grafo a partir de um arquivo de texto, lendo vértices e arestas formatadas.
// entradas: 
//   - caminhoArquivo: caminho do arquivo contendo os dados do grafo.
// saídas: 
//   - Retorna um ponteiro para a estrutura do grafo carregado a partir do arquivo.
Grafo* carregarGrafo(const char* caminhoArquivo);

// Gera o arquivo DOT representando o grafo, contendo a definição dos vértices e arestas.
// entradas:
//   - grafo: ponteiro para a estrutura do grafo a ser representado.
//   - nomeArquivo: nome do arquivo de saída para o arquivo DOT.
// saídas:
//   - Nenhuma. O arquivo DOT é gerado no caminho especificado.
void gerarDOT(Grafo* grafo, const char* nomeArquivo);

// Função para gerar a imagem do grafo no formato PNG usando o Graphviz
// entradas:
//   - grafo: ponteiro para a estrutura do grafo a ser representado.
//   - caminhoArquivo: caminho onde a imagem PNG gerada será salva (sem a extensão).
// saídas:
//   - Nenhuma. A imagem PNG é gerada e salva no caminho especificado.
void gerarImagemGrafo(Grafo* grafo, const char* caminhoArquivo);

#endif