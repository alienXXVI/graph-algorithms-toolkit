#include "graphviz.h"

void gerarDOT(Grafo* grafo, const char* nomeArquivo) {
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

void gerarImagemGrafo(const char* nomeArquivoDOT, const char* nomeImagem) {
    char comando[256];
    snprintf(comando, sizeof(comando), "dot -Tpng %s -o %s", nomeArquivoDOT, nomeImagem);
    system(comando);  // Executa o comando no terminal

    // Abre a imagem gerada
    snprintf(comando, sizeof(comando), "start %s", nomeImagem);
    system(comando);
}

void gerarImagemDOT(const char* nomeDOT, const char* nomeImagem) {
    char comando[512];
    snprintf(comando, sizeof(comando), "dot -Tpng %s -o %s", nomeDOT, nomeImagem);
    int resultado = system(comando);
    if (resultado != 0) {
        printf("Erro ao gerar a imagem com Graphviz.\n");
    } else {
        printf("Imagem gerada: %s\n", nomeImagem);
    }
}
