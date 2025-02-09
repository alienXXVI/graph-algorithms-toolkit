#include "./headers/algoritmos.h"

int main() {
    // Carregar o grafo a partir de um arquivo
    Grafo* grafo = carregarGrafo("./input/grafo.txt");
    if (grafo == NULL) {
        return 1; // Encerrar o programa se o grafo não puder ser carregado
    }

    // Imprimir o grafo para verificar o carregamento
    printf("Grafo Original:\n");
    imprimirGrafo(grafo);

    printf("\nBellman-Ford a partir do vertice %d:\n", 1);
    bellmanFord(grafo, 2);

    // Liberar a memória alocada para o grafo
    liberarGrafo(grafo);
    return 0;
}
