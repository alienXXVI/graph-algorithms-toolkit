#include "graphviz.h"

int main() {
    // Carregar o grafo a partir de um arquivo
    Grafo* grafo = carregarGrafo("grafo.txt");
    if (grafo == NULL) {
        return 1; // Encerrar o programa se o grafo não puder ser carregado
    }

    // Imprimir o grafo para verificar o carregamento
    imprimirGrafo(grafo);
    gerarDOT(grafo, "grafo.dot");
    gerarImagemDOT("grafo.dot", "grafo.png");


    // Liberar a memória alocada para o grafo
    liberarGrafo(grafo);
    return 0;
}