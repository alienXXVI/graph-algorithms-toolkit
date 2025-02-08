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

    // Determinar e exibir as componentes fortemente conexas
    printf("\nArvore Geradora Minima (Kruskal):\n");
    kruskal(grafo);

    // Liberar a memória alocada para o grafo
    liberarGrafo(grafo);
    return 0;
}
