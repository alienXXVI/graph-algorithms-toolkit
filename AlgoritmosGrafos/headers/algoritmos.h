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
// -- FILA --

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
// -- BUSCA EM PROFUNDIDADE --

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
// -- BUSCA EM LARGURA --

// Executa a busca em largura (BFS) a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de início da busca.
// saídas: 
//   - Nenhuma (os vértices visitados são impressos na tela).
void buscaLargura(Grafo* grafo, int origem);


// -------------------------------------
// -- BELLMAN-FORD --

// Inicializa as distâncias e predecessores para o algoritmo de Bellman-Ford.
// entradas: 
//   - caminhos: vetor de estruturas para armazenar as menores distâncias e predecessores.
//   - numVertices: número total de vértices no grafo.
//   - origem: vértice de origem para o cálculo das menores distâncias.
// saídas: 
//   - O vetor de caminhos é atualizado com a distância inicial infinita para todos os vértices, 
//     exceto a origem, que recebe distância 0.
void inicializarCaminhos(Caminho* caminhos, int numVertices, int origem);

// Imprime o caminho mínimo do vértice de origem até um destino específico.
// entradas: 
//   - caminhos: vetor de estruturas contendo as informações de predecessores dos vértices.
//   - destino: índice do vértice cujo caminho será impresso.
// saídas: 
//   - Exibe na saída padrão o caminho mínimo do vértice de origem até o destino.
void imprimirCaminho(Caminho* caminhos, int destino);

// Implementa o algoritmo de Bellman-Ford para encontrar os menores caminhos a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo direcionado a ser processado.
//   - origem: índice do vértice de origem para o cálculo dos caminhos mínimos.
// saídas: 
//   - Exibe na saída padrão os menores caminhos a partir da origem para cada vértice do grafo.
//   - Se houver um ciclo de peso negativo, exibe uma mensagem de erro e encerra a execução.
void bellmanFord(Grafo* grafo, int origem);


// -------------------------------------
// -- CONJUNTO UNIÃO-BUSCA --

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
// -- KRUSKAL --

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
// -- COMPONENTES CONEXAS --

// Função auxiliar para busca em profundidade (DFS)
// entradas: 
//   - grafo: grafo no qual a busca em profundidade será realizada.
//   - vertice: vértice inicial para a busca.
//   - visitado: array que indica quais vértices já foram visitados.
//   - componente: array para armazenar os vértices da componente conexa.
//   - tamanho: variável para manter o tamanho da componente conexa.
void dfs(Grafo* grafo, int vertice, bool* visitado, int* componente, int* tamanho);

// Função para encontrar e exibir componentes conexas
// entradas: 
//   - grafo: grafo no qual as componentes conexas serão encontradas.
// saídas: 
//   - Exibe as componentes conexas no grafo.
void encontrarComponentesConexas(Grafo* grafo);


// -------------------------------------
// -- COMPONENTES FORTEMENTE CONEXAS --

// Função auxiliar para empilhar vértices na primeira DFS
// entradas: 
//   - grafo: grafo no qual a busca em profundidade será realizada.
//   - v: vértice atual da busca.
//   - visitado: array que indica quais vértices já foram visitados.
//   - pilha: array que armazenará os vértices em ordem pós-ordem.
//   - topo: variável que indica o topo da pilha.
void dfsPilha(Grafo* grafo, int v, bool visitado[], int pilha[], int* topo);

// Função auxiliar para DFS no grafo transposto
// entradas: 
//   - grafoT: grafo transposto para realizar a DFS.
//   - v: vértice atual da DFS.
//   - visitado: array que indica quais vértices já foram visitados.
//   - componente: array para armazenar os vértices da componente fortemente conexa.
//   - tamanho: variável para manter o tamanho da componente fortemente conexa.
void dfsComponente(Grafo* grafoT, int v, bool visitado[], int componente[], int* tamanho);

// Função para encontrar as componentes fortemente conexas e imprimi-las
// entradas: 
//   - grafo: grafo direcionado onde as componentes fortemente conexas serão encontradas.
// saídas: 
//   - Exibe as componentes fortemente conexas e gera uma imagem do grafo com as componentes.
void encontrarCFC(Grafo* grafo);

// Função para gerar imagem do grafo com cores por componente
// entradas: 
//   - grafo: grafo que contém as componentes fortemente conexas.
//   - nomeArquivo: nome do arquivo onde a imagem será salva.
// saídas: 
//   - Gera uma imagem do grafo com as componentes fortemente conexas coloridas.
void gerarImagemCFC(Grafo* grafo, const char* nomeArquivo);


#endif