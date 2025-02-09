#include "../headers/algoritmos.h"
#include <stdbool.h>

#define OUTPUT_DIR "./output/"

// -------------------------------------
// -- FILA --

// Cria e inicializa uma fila com a capacidade especificada.
// entradas: 
//   - capacidade: número máximo de elementos que a fila pode armazenar.
// saídas: 
//   - Retorna um ponteiro para a estrutura de fila criada.
Fila* criarFila(int capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->dados = (int*)malloc(capacidade * sizeof(int));
    fila->frente = 0;
    fila->tras = 0;
    fila->capacidade = capacidade;
    return fila;
}

// Verifica se a fila está vazia.
// entradas: 
//   - fila: ponteiro para a estrutura da fila.
// saídas: 
//   - Retorna 1 se a fila estiver vazia, 0 caso contrário.
int filaVazia(Fila* fila) {
    return fila->frente == fila->tras;
}

// Insere um elemento no final da fila.
// entradas: 
//   - fila: ponteiro para a estrutura da fila.
//   - valor: elemento a ser inserido na fila.
// saídas: 
//   - Nenhuma (a fila é modificada diretamente).
void enfileirar(Fila* fila, int valor) {
    fila->dados[fila->tras++] = valor;
}

// Remove e retorna o elemento na frente da fila.
// entradas: 
//   - fila: ponteiro para a estrutura da fila.
// saídas: 
//   - Retorna o elemento removido da fila.
int desenfileirar(Fila* fila) {
    return fila->dados[fila->frente++];
}

// Libera a memória alocada para a fila.
// entradas: 
//   - fila: ponteiro para a estrutura da fila a ser liberada.
// saídas: 
//   - Nenhuma (a memória é liberada diretamente).
void liberarFila(Fila* fila) {
    free(fila->dados);
    free(fila);
}


// -------------------------------------
// -- BUSCA EM PROFUNDIDADE --

// Executa a busca em profundidade (DFS) de forma recursiva a partir de um vértice.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - vertice: índice do vértice atual na busca.
//   - visitado: vetor que armazena se um vértice já foi visitado.
// saídas: 
//   - Nenhuma (os vértices são visitados e impressos durante a execução).
void dfsRecursivo(Grafo* grafo, int vertice, int* visitado) {
    visitado[vertice] = 1;
    printf("%d - ", vertice);
    
    No* adjacente = grafo->listaAdj[vertice];
    while (adjacente) {
        if (!visitado[adjacente->aresta.destino]) {
            dfsRecursivo(grafo, adjacente->aresta.destino, visitado);
        }
        adjacente = adjacente->proximo;
    }
}

// Executa a busca em profundidade (DFS) a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de início da busca.
// saídas: 
//   - Nenhuma (os vértices visitados são impressos na tela).
void buscaProfundidade(Grafo* grafo, int origem) {
    if (!grafo || origem >= grafo->numVertices || origem < 0) {
        printf("Erro: Grafo invalido ou vertice de origem fora do intervalo.\n");
        return;
    }
    
    int* visitado = (int*)calloc(grafo->numVertices, sizeof(int));
    if (!visitado) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return;
    }
    
    printf("DFS: ");
    dfsRecursivo(grafo, origem, visitado);
    printf("\n");
    free(visitado);
}


// -------------------------------------
// -- BUSCA EM LARGURA --

// Executa a busca em largura (BFS) a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de início da busca.
// saídas: 
//   - Nenhuma (os vértices visitados são impressos na tela).
void buscaLargura(Grafo* grafo, int origem) {
    if (!grafo || origem >= grafo->numVertices || origem < 0) {
        printf("Erro: Grafo invalido ou vertice de origem fora do intervalo.\n");
        return;
    }
    
    int* visitado = (int*)calloc(grafo->numVertices, sizeof(int));
    if (!visitado) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return;
    }
    
    printf("BFS: ");
    Fila* fila = criarFila(grafo->numVertices);
    enfileirar(fila, origem);
    visitado[origem] = 1;
    
    while (!filaVazia(fila)) {
        int vertice = desenfileirar(fila);
        printf("%d - ", vertice);
        
        No* adjacente = grafo->listaAdj[vertice];
        while (adjacente) {
            if (!visitado[adjacente->aresta.destino]) {
                enfileirar(fila, adjacente->aresta.destino);
                visitado[adjacente->aresta.destino] = 1;
            }
            adjacente = adjacente->proximo;
        }
    }
    
    printf("\n");
    liberarFila(fila);
    free(visitado);
}


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
void inicializarCaminhos(Caminho* caminhos, int numVertices, int origem) {
    for (int i = 0; i < numVertices; i++) {
        caminhos[i].distancia = INT_MAX;
        caminhos[i].predecessor = -1;
    }
    caminhos[origem].distancia = 0;
}

// Imprime o caminho mínimo do vértice de origem até um destino específico.
// entradas: 
//   - caminhos: vetor de estruturas contendo as informações de predecessores dos vértices.
//   - destino: índice do vértice cujo caminho será impresso.
// saídas: 
//   - Exibe na saída padrão o caminho mínimo do vértice de origem até o destino.
void imprimirCaminho(Caminho* caminhos, int destino) {
    if (caminhos[destino].predecessor == -1) {
        printf("%d", destino);
        return;
    }
    imprimirCaminho(caminhos, caminhos[destino].predecessor);
    printf(" - %d", destino);
}

// Implementa o algoritmo de Bellman-Ford para encontrar os menores caminhos a partir de um vértice de origem.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo direcionado a ser processado.
//   - origem: índice do vértice de origem para o cálculo dos caminhos mínimos.
// saídas: 
//   - Exibe na saída padrão os menores caminhos a partir da origem para cada vértice do grafo.
//   - Se houver um ciclo de peso negativo, exibe uma mensagem de erro e encerra a execução.
void bellmanFord(Grafo* grafo, int origem) {
    // Verifica se o grafo é orientado
    if (!grafo->orientado) {
        printf("Erro: O algoritmo de Bellman-Ford so pode ser aplicado a grafos orientados.\n");
        return;
    }

    int numVertices = grafo->numVertices;
    Caminho caminhos[numVertices];

    inicializarCaminhos(caminhos, numVertices, origem);

    // Relaxamento das arestas (numVertices - 1 vezes)
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            No* no = grafo->listaAdj[u];
            while (no) {
                int v = no->aresta.destino;
                int peso = no->aresta.peso;

                if (caminhos[u].distancia != INT_MAX && caminhos[u].distancia + peso < caminhos[v].distancia) {
                    caminhos[v].distancia = caminhos[u].distancia + peso;
                    caminhos[v].predecessor = u;
                }
                no = no->proximo;
            }
        }
    }

    // Verificação de ciclos de peso negativo
    for (int u = 0; u < numVertices; u++) {
        No* no = grafo->listaAdj[u];
        while (no) {
            int v = no->aresta.destino;
            int peso = no->aresta.peso;

            if (caminhos[u].distancia != INT_MAX && caminhos[u].distancia + peso < caminhos[v].distancia) {
                printf("Erro: O grafo contem um ciclo de peso negativo.\n");
                return;
            }
            no = no->proximo;
        }
    }

    // Impressão dos menores caminhos
    printf("Origem: %d\n", origem);
    for (int i = 0; i < numVertices; i++) {
        printf("Destino: %d ", i);
        if (caminhos[i].distancia == INT_MAX) {
            printf("dist.: Infinito (Sem caminho)\n");
        } else {
            printf("dist.: %d caminho: ", caminhos[i].distancia);
            imprimirCaminho(caminhos, i);
            printf("\n");
        }
    }
}


// -------------------------------------
// -- CONJUNTO UNIÃO-BUSCA --

// Cria e inicializa um conjunto para a estrutura união-busca (disjoint-set).
// entradas: 
//   - numVertices: número total de vértices no conjunto.
// saídas: 
//   - Retorna um ponteiro para a estrutura de conjunto inicializada.
Conjunto* criarConjunto(int numVertices) {
    Conjunto* conjunto = (Conjunto*)malloc(sizeof(Conjunto));
    conjunto->pai = (int*)malloc(numVertices * sizeof(int));
    conjunto->rank = (int*)malloc(numVertices * sizeof(int));
    conjunto->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        conjunto->pai[i] = i;
        conjunto->rank[i] = 0;
    }
    return conjunto;
}

// Encontra o representante (raiz) do conjunto ao qual um vértice pertence, aplicando compressão de caminho.
// entradas: 
//   - conjunto: ponteiro para a estrutura do conjunto união-busca.
//   - vertice: índice do vértice a ser encontrado.
// saídas: 
//   - Retorna o representante (raiz) do conjunto do vértice.
int encontrar(Conjunto* conjunto, int vertice) {
    if (conjunto->pai[vertice] != vertice) {
        conjunto->pai[vertice] = encontrar(conjunto, conjunto->pai[vertice]);
    }
    return conjunto->pai[vertice];
}

// Une dois conjuntos disjuntos, aplicando a técnica de união por rank.
// entradas: 
//   - conjunto: ponteiro para a estrutura do conjunto união-busca.
//   - raiz1: representante do primeiro conjunto.
//   - raiz2: representante do segundo conjunto.
// saídas: 
//   - Nenhuma (modifica a estrutura do conjunto unindo os elementos).
void unir(Conjunto* conjunto, int raiz1, int raiz2) {
    if (conjunto->rank[raiz1] > conjunto->rank[raiz2]) {
        conjunto->pai[raiz2] = raiz1;
    } else if (conjunto->rank[raiz1] < conjunto->rank[raiz2]) {
        conjunto->pai[raiz1] = raiz2;
    } else {
        conjunto->pai[raiz2] = raiz1;
        conjunto->rank[raiz1]++;
    }
}

// Libera a memória alocada para a estrutura do conjunto união-busca.
// entradas: 
//   - conjunto: ponteiro para a estrutura do conjunto a ser liberado.
// saídas: 
//   - Nenhuma (memória desalocada).
void liberarConjunto(Conjunto* conjunto) {
    free(conjunto->pai);
    free(conjunto->rank);
    free(conjunto);
}


// -------------------------------------
// -- KRUSKAL --

// Compara duas arestas pelo peso, utilizada na ordenação com qsort.
// entradas: 
//   - a: ponteiro para a primeira aresta.
//   - b: ponteiro para a segunda aresta.
// saídas: 
//   - Retorna um valor negativo se a primeira aresta for menor, 
//     zero se forem iguais, e um valor positivo se for maior.
int compararArestas(const void* a, const void* b) {
    return ((ArestaOrdenada*)a)->peso - ((ArestaOrdenada*)b)->peso;
}

// Implementa o algoritmo de Kruskal para encontrar a Árvore Geradora Mínima (AGM) de um grafo.
// entradas: 
//   - grafo: ponteiro para o grafo sobre o qual o algoritmo será executado.
// saídas: 
//   - Nenhuma (exibe a AGM no console e gera um arquivo DOT e PNG para visualização).
void kruskal(Grafo* grafo) {
    if (grafo->orientado) {
        printf("Erro: O algoritmo de Kruskal nao pode ser aplicado a grafos orientados.\n");
        return;
    }
    
    int numArestas = 0;
    for (int i = 0; i < grafo->numVertices; i++) {
        No* atual = grafo->listaAdj[i];
        while (atual) {
            if (i < atual->aresta.destino) {
                numArestas++;
            }
            atual = atual->proximo;
        }
    }

    if (numArestas < grafo->numVertices - 1) {
        printf("Erro: O grafo nao possui arestas suficientes para formar uma Arvore Geradora Minima.\n");
        return;
    }

    ArestaOrdenada* arestas = (ArestaOrdenada*)malloc(numArestas * sizeof(ArestaOrdenada));
    int index = 0;
    for (int i = 0; i < grafo->numVertices; i++) {
        No* atual = grafo->listaAdj[i];
        while (atual) {
            if (i < atual->aresta.destino) {
                arestas[index++] = (ArestaOrdenada){i, atual->aresta.destino, atual->aresta.peso};
            }
            atual = atual->proximo;
        }
    }
    
    qsort(arestas, numArestas, sizeof(ArestaOrdenada), compararArestas);

    Conjunto* conjunto = criarConjunto(grafo->numVertices);
    int pesoTotal = 0;
    ArestaOrdenada* AGM = (ArestaOrdenada*)malloc((grafo->numVertices - 1) * sizeof(ArestaOrdenada));
    int cont = 0;

    for (int i = 0; i < numArestas && cont < grafo->numVertices - 1; i++) {
        int raizOrigem = encontrar(conjunto, arestas[i].origem);
        int raizDestino = encontrar(conjunto, arestas[i].destino);

        if (raizOrigem != raizDestino) {
            AGM[cont++] = arestas[i];
            pesoTotal += arestas[i].peso;
            unir(conjunto, raizOrigem, raizDestino);
        }
    }

    if (cont != grafo->numVertices - 1) {
        printf("Erro: O grafo nao eh conexo, impossibilitando a aplicacao do algoritmo de Kruskal.\n");
        free(arestas);
        free(AGM);
        liberarConjunto(conjunto);
        return;
    }

    printf("peso total: %d\n", pesoTotal);
    printf("arestas:");
    for (int i = 0; i < cont; i++) {
        printf(" (%d,%d)", AGM[i].origem, AGM[i].destino);
    }
    printf("\n");

    gerarImagemKruskal(grafo, AGM, cont, "./output/kruskal.dot", "./output/kruskal.png");

    free(arestas);
    free(AGM);
    liberarConjunto(conjunto);
}

// Gera um arquivo DOT e uma imagem destacando a Árvore Geradora Mínima (AGM) encontrada pelo algoritmo de Kruskal.
// entradas: 
//   - grafo: ponteiro para o grafo original.
//   - AGM: array de arestas pertencentes à AGM.
//   - numArestas: número de arestas na AGM.
//   - nomeDOT: nome do arquivo DOT a ser gerado.
//   - nomeImagem: nome do arquivo de imagem resultante.
// saídas: 
//   - Nenhuma (gera os arquivos DOT e imagem).
void gerarImagemKruskal(Grafo* grafo, ArestaOrdenada* AGM, int numArestas, const char* nomeDOT, const char* nomeImagem) {
    FILE* arquivo = fopen(nomeDOT, "w");
    if (!arquivo) {
        printf("Erro ao criar arquivo DOT.\n");
        return;
    }
    
    fprintf(arquivo, "%s G {\n", grafo->orientado ? "digraph" : "graph");
    
    for (int i = 0; i < grafo->numVertices; i++) {
        fprintf(arquivo, "    %d;\n", i);
    }

    char* seta = grafo->orientado ? " -> " : " -- ";
    for (int i = 0; i < grafo->numVertices; i++) {
        No* atual = grafo->listaAdj[i];
        while (atual) {
            if (i < atual->aresta.destino) {
                int naAGM = 0;
                for (int j = 0; j < numArestas; j++) {
                    if ((AGM[j].origem == i && AGM[j].destino == atual->aresta.destino) ||
                        (AGM[j].origem == atual->aresta.destino && AGM[j].destino == i)) {
                        naAGM = 1;
                        break;
                    }
                }
                fprintf(arquivo, "    %d%s%d [label=\"%d\"%s];\n", i, seta, atual->aresta.destino, atual->aresta.peso, naAGM ? ", color=red, penwidth=2.0" : "");
            }
            atual = atual->proximo;
        }
    }
    
    fprintf(arquivo, "}\n");
    fclose(arquivo);
    
    char comando[512];
    snprintf(comando, sizeof(comando), "dot -Tpng %s -o %s", nomeDOT, nomeImagem);
    system(comando);
    printf("Imagem gerada: %s\n", nomeImagem);
}


// -------------------------------------
// -- COMPONENTES CONEXAS --

// Função auxiliar para busca em profundidade (DFS)
// entradas: 
//   - grafo: grafo no qual a busca em profundidade será realizada.
//   - vertice: vértice inicial para a busca.
//   - visitado: array que indica quais vértices já foram visitados.
//   - componente: array para armazenar os vértices da componente conexa.
//   - tamanho: variável para manter o tamanho da componente conexa.
void dfs(Grafo* grafo, int vertice, bool* visitado, int* componente, int* tamanho) {
    visitado[vertice] = true;
    componente[*tamanho] = vertice;
    (*tamanho)++;
    
    No* atual = grafo->listaAdj[vertice];
    while (atual) {
        int v = atual->aresta.destino;
        if (!visitado[v]) {
            dfs(grafo, v, visitado, componente, tamanho);
        }
        atual = atual->proximo;
    }
}

// Função para encontrar e exibir componentes conexas
// entradas: 
//   - grafo: grafo no qual as componentes conexas serão encontradas.
// saídas: 
//   - Exibe as componentes conexas no grafo.
void encontrarComponentesConexas(Grafo* grafo) {
    // Verifica se o grafo é não orientado
    if (grafo->orientado) {
        printf("Erro: O algoritmo de componentes conexas so pode ser aplicado a grafos nao orientados.\n");
        return;
    }
    
    int numVertices = grafo->numVertices;
    bool visitado[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    // Armazena as componentes conexas
    int* componentes[numVertices];
    int tamanhos[numVertices];
    int numComponentes = 0;
    
    // Executa DFS para cada componente conexa
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            componentes[numComponentes] = (int*)malloc(numVertices * sizeof(int));
            tamanhos[numComponentes] = 0;
            dfs(grafo, i, visitado, componentes[numComponentes], &tamanhos[numComponentes]);
            numComponentes++;
        }
    }
    
    // Ordena as componentes por tamanho decrescente
    for (int i = 0; i < numComponentes - 1; i++) {
        for (int j = i + 1; j < numComponentes; j++) {
            if (tamanhos[i] < tamanhos[j]) {
                int* tempComp = componentes[i];
                int tempTam = tamanhos[i];
                componentes[i] = componentes[j];
                tamanhos[i] = tamanhos[j];
                componentes[j] = tempComp;
                tamanhos[j] = tempTam;
            }
        }
    }
    
    // Exibe as componentes
    for (int i = 0; i < numComponentes; i++) {
        printf("Componente %d: ", i + 1);
        for (int j = 0; j < tamanhos[i]; j++) {
            printf("%d", componentes[i][j]);
            if (j < tamanhos[i] - 1) printf(", ");
        }
        printf("\n");
        free(componentes[i]);
    }
}


// -------------------------------------
// -- COMPONENTES FORTEMENTE CONEXAS --

// Função auxiliar para empilhar vértices na primeira DFS
// entradas: 
//   - grafo: grafo no qual a busca em profundidade será realizada.
//   - v: vértice atual da busca.
//   - visitado: array que indica quais vértices já foram visitados.
//   - pilha: array que armazenará os vértices em ordem pós-ordem.
//   - topo: variável que indica o topo da pilha.
void dfsPilha(Grafo* grafo, int v, bool visitado[], int pilha[], int* topo) {
    visitado[v] = true;
    
    for (No* no = grafo->listaAdj[v]; no != NULL; no = no->proximo) {
        if (!visitado[no->aresta.destino]) {
            dfsPilha(grafo, no->aresta.destino, visitado, pilha, topo);
        }
    }
    pilha[(*topo)++] = v;
}

// Função auxiliar para DFS no grafo transposto
// entradas: 
//   - grafoT: grafo transposto para realizar a DFS.
//   - v: vértice atual da DFS.
//   - visitado: array que indica quais vértices já foram visitados.
//   - componente: array para armazenar os vértices da componente fortemente conexa.
//   - tamanho: variável para manter o tamanho da componente fortemente conexa.
void dfsComponente(Grafo* grafoT, int v, bool visitado[], int componente[], int* tamanho) {
    visitado[v] = true;
    componente[(*tamanho)++] = v;
    
    for (No* no = grafoT->listaAdj[v]; no != NULL; no = no->proximo) {
        if (!visitado[no->aresta.destino]) {
            dfsComponente(grafoT, no->aresta.destino, visitado, componente, tamanho);
        }
    }
}

// Função para encontrar as componentes fortemente conexas e imprimi-las
// entradas: 
//   - grafo: grafo direcionado onde as componentes fortemente conexas serão encontradas.
// saídas: 
//   - Exibe as componentes fortemente conexas e gera uma imagem do grafo com as componentes.
void encontrarCFC(Grafo* grafo) {
    if (!grafo->orientado) {
        printf("Erro: O algoritmo de componentes fortemente conexas so pode ser aplicado a grafos direcionados.\n");
        return;
    }
    
    int numVertices = grafo->numVertices;
    bool visitado[numVertices];
    int pilha[numVertices], topo = 0;
    
    memset(visitado, false, sizeof(visitado));
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            dfsPilha(grafo, i, visitado, pilha, &topo);
        }
    }
    
    Grafo* grafoT = criarGrafo(numVertices, 1);
    for (int v = 0; v < numVertices; v++) {
        for (No* no = grafo->listaAdj[v]; no != NULL; no = no->proximo) {
            adicionarAresta(grafoT, no->aresta.destino, v, no->aresta.peso);
        }
    }
    
    memset(visitado, false, sizeof(visitado));
    int componentes[numVertices][numVertices], tamanhos[numVertices];
    int numComponentes = 0;
    
    while (topo > 0) {
        int v = pilha[--topo];
        if (!visitado[v]) {
            tamanhos[numComponentes] = 0;
            dfsComponente(grafoT, v, visitado, componentes[numComponentes], &tamanhos[numComponentes]);
            numComponentes++;
        }
    }
    
    // Imprimir componentes
    for (int i = 0; i < numComponentes; i++) {
        printf("Componente %d:", i + 1);
        for (int j = 0; j < tamanhos[i]; j++) {
            printf(" %d", componentes[i][j]);
        }
        printf("\n");
    }
    
    // Gerar imagem na pasta ./output/
    char caminhoSaida[256];
    sprintf(caminhoSaida, "%sgrafoCFC.png", OUTPUT_DIR);
    gerarImagemCFC(grafo, caminhoSaida);
    
    liberarGrafo(grafoT);
}

// Função para gerar imagem do grafo com cores por componente
// entradas: 
//   - grafo: grafo que contém as componentes fortemente conexas.
//   - nomeArquivo: nome do arquivo onde a imagem será salva.
// saídas: 
//   - Gera uma imagem do grafo com as componentes fortemente conexas coloridas.
void gerarImagemCFC(Grafo* grafo, const char* nomeArquivo) {
    char caminhoDot[256];
    sprintf(caminhoDot, "%sgrafoCFC.dot", OUTPUT_DIR);
    
    FILE* arquivo = fopen(caminhoDot, "w");
    if (!arquivo) {
        printf("Erro ao criar arquivo DOT.\n");
        return;
    }
    
    fprintf(arquivo, "digraph G {\n");
    fprintf(arquivo, "    node [style=filled];\n");
    
    int numVertices = grafo->numVertices;
    bool visitado[numVertices];
    int pilha[numVertices], topo = 0;
    memset(visitado, false, sizeof(visitado));
    
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            dfsPilha(grafo, i, visitado, pilha, &topo);
        }
    }
    
    Grafo* grafoT = criarGrafo(numVertices, 1);
    for (int v = 0; v < numVertices; v++) {
        for (No* no = grafo->listaAdj[v]; no != NULL; no = no->proximo) {
            adicionarAresta(grafoT, no->aresta.destino, v, no->aresta.peso);
        }
    }
    
    memset(visitado, false, sizeof(visitado));
    int componentes[numVertices][numVertices], tamanhos[numVertices], numComponentes = 0;
    
    while (topo > 0) {
        int v = pilha[--topo];
        if (!visitado[v]) {
            tamanhos[numComponentes] = 0;
            dfsComponente(grafoT, v, visitado, componentes[numComponentes], &tamanhos[numComponentes]);
            numComponentes++;
        }
    }
    
    const char* cores[] = {"red", "blue", "green", "yellow", "cyan", "magenta", "orange", "pink"};
    for (int i = 0; i < numComponentes; i++) {
        for (int j = 0; j < tamanhos[i]; j++) {
            fprintf(arquivo, "    %d [fillcolor=%s];\n", componentes[i][j], cores[i % 8]);
        }
    }
    
    for (int v = 0; v < numVertices; v++) {
        for (No* no = grafo->listaAdj[v]; no != NULL; no = no->proximo) {
            fprintf(arquivo, "    %d -> %d;\n", v, no->aresta.destino);
        }
    }
    
    fprintf(arquivo, "}\n");
    fclose(arquivo);
    
    char comando[256];
    sprintf(comando, "dot -Tpng %s -o %s", caminhoDot, nomeArquivo);
    system(comando);
    printf("Imagem gerada: %s\n", nomeArquivo);
    
    liberarGrafo(grafoT);
}
