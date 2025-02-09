#include "../headers/grafo.h"

// Cria um novo nó na lista de adjacências de um grafo.
// entradas: 
//   - destino: vértice de destino da aresta.
//   - peso: peso da aresta associada ao nó.
// saídas: 
//   - Retorna um ponteiro para o novo nó criado.
No* criarNo(int destino, int peso) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->aresta.destino = destino;
    novoNo->aresta.peso = peso;
    novoNo->proximo = NULL;
    return novoNo;
}

// Cria um grafo com um número específico de vértices, podendo ser orientado ou não.
// entradas: 
//   - numVertices: número total de vértices no grafo.
//   - orientado: indica se o grafo é orientado (1 para sim, 0 para não).
// saídas: 
//   - Retorna um ponteiro para a estrutura do grafo inicializada.
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

// Adiciona uma aresta ao grafo, com inserção ordenada na lista de adjacências.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo.
//   - origem: vértice de origem da aresta.
//   - destino: vértice de destino da aresta.
//   - peso: peso associado à aresta.
// saídas: 
//   - Nenhuma (modifica a estrutura do grafo adicionando a aresta).
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

// Libera a memória alocada para a estrutura do grafo e suas listas de adjacências.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo a ser liberado.
// saídas: 
//   - Nenhuma (memória desalocada).
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

// Imprime a lista de adjacências do grafo, exibindo seus vértices e conexões.
// entradas: 
//   - grafo: ponteiro para a estrutura do grafo a ser impresso.
// saídas: 
//   - Nenhuma (exibe a estrutura do grafo no console).
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

// Carrega um grafo a partir de um arquivo de texto, lendo vértices e arestas formatadas.
// entradas: 
//   - caminhoArquivo: caminho do arquivo contendo os dados do grafo.
// saídas: 
//   - Retorna um ponteiro para a estrutura do grafo carregado a partir do arquivo.
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

// Gera o arquivo DOT representando o grafo, contendo a definição dos vértices e arestas.
// entradas:
//   - grafo: ponteiro para a estrutura do grafo a ser representado.
//   - nomeArquivo: nome do arquivo de saída para o arquivo DOT.
// saídas:
//   - Nenhuma. O arquivo DOT é gerado no caminho especificado.
void gerarDOT(Grafo* grafo, const char* nomeArquivo) {
    // Abre o arquivo DOT para gravação na pasta .\output
    FILE* arquivoDOT = fopen(nomeArquivo, "w");
    if (arquivoDOT == NULL) {
        printf("Erro ao criar o arquivo DOT.\n");
        return;
    }

    // Escrever o cabeçalho do arquivo DOT
    if (grafo->orientado) {
        fprintf(arquivoDOT, "digraph G {\n");
    } else {
        fprintf(arquivoDOT, "graph G {\n");
    }

    // Escrever os vértices
    for (int i = 0; i < grafo->numVertices; i++) {
        fprintf(arquivoDOT, "  %d;\n", i);
    }

    // Escrever as arestas
    for (int i = 0; i < grafo->numVertices; i++) {
        No* atual = grafo->listaAdj[i];
        while (atual != NULL) {
            if (grafo->orientado || i < atual->aresta.destino) { // Evitar duplicação em grafos não orientados
                fprintf(arquivoDOT, "  %d %s %d [label=\"%d\"];\n",
                        i,
                        grafo->orientado ? "->" : "--",
                        atual->aresta.destino,
                        atual->aresta.peso);
            }
            atual = atual->proximo;
        }
    }

    fprintf(arquivoDOT, "}\n");
    fclose(arquivoDOT);
}

// Função para gerar a imagem do grafo no formato PNG usando o Graphviz
// entradas:
//   - grafo: ponteiro para a estrutura do grafo a ser representado.
//   - caminhoArquivo: caminho onde a imagem PNG gerada será salva (sem a extensão).
// saídas:
//   - Nenhuma. A imagem PNG é gerada e salva no caminho especificado.
void gerarImagemGrafo(Grafo* grafo, const char* caminhoArquivo) {
    // Criar nome base para o arquivo (sem diretórios)
    const char* nomeBase = strrchr(caminhoArquivo, '\\');
    if (nomeBase == NULL) {
        nomeBase = caminhoArquivo;  // Se não houver barra invertida, usa o nome direto
    } else {
        nomeBase++;  // Pular a barra invertida
    }

    // Adicionar a pasta de saída
    char nomeArquivoDOT[200];
    snprintf(nomeArquivoDOT, sizeof(nomeArquivoDOT), ".\\output\\%s.dot", nomeBase);

    // Gerar o arquivo DOT
    gerarDOT(grafo, nomeArquivoDOT);

    // Gerar nome para o arquivo .png
    char nomeImagem[200];
    snprintf(nomeImagem, sizeof(nomeImagem), ".\\output\\%s.png", nomeBase);

    // Gerar a imagem .png com o Graphviz
    char comando[512];
    snprintf(comando, sizeof(comando), "dot -Tpng %s -o %s", nomeArquivoDOT, nomeImagem);
    int resultado = system(comando);
    if (resultado != 0) {
        printf("Erro ao gerar a imagem.\n");
    } else {
        printf("Imagem gerada com sucesso: %s\n", nomeImagem);
    }
}
