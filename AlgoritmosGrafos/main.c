#include "./headers/algoritmos.h"

void exibirMenu() {
    printf("\nMenu de Algoritmos de Grafos\n");
    printf("1. Carregar Grafo\n");
    printf("2. Executar Kruskal\n");
    printf("3. Executar Componentes Fortemente Conexas (CFC)\n");
    printf("4. Executar Busca em Profundidade (DFS)\n");
    printf("5. Executar Busca em Largura (BFS)\n");
    printf("6. Executar Bellman-Ford\n");
    printf("7. Executar Componentes Conexas\n");
    printf("0. Sair\n");
}

int main() {
    Grafo* grafo = NULL;
    int opcao;
    char caminho[100];

    while (1) {
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Carregar Grafo
                printf("Informe o caminho do arquivo do grafo: ");
                scanf("%s", caminho);
                grafo = carregarGrafo(caminho);
                if (grafo == NULL) {
                    printf("Erro ao carregar o grafo.\n");
                } else {
                    printf("Grafo carregado com sucesso.\n");
                    imprimirGrafo(grafo);
                }
                break;

            case 2: // Executar Kruskal
                if (grafo != NULL) {
                    printf("\nArvore Geradora Minima (Kruskal):\n");
                    kruskal(grafo);
                } else {
                    printf("Carregue o grafo primeiro.\n");
                }
                break;

            case 3: // Executar CFC
                if (grafo != NULL) {
                    printf("\nComponentes Fortemente Conexas:\n");
                    encontrarCFC(grafo);
                } else {
                    printf("Carregue o grafo primeiro.\n");
                }
                break;

            case 4: // Executar DFS
                if (grafo != NULL) {
                    int vertice;
                    printf("Informe o vertice de partida para DFS: ");
                    scanf("%d", &vertice);
                    printf("\nBusca em Profundidade (DFS) a partir do vertice %d:\n", vertice);
                    buscaProfundidade(grafo, vertice);
                } else {
                    printf("Carregue o grafo primeiro.\n");
                }
                break;

            case 5: // Executar BFS
                if (grafo != NULL) {
                    int vertice;
                    printf("Informe o vertice de partida para BFS: ");
                    scanf("%d", &vertice);
                    printf("\nBusca em Largura (BFS) a partir do vertice %d:\n", vertice);
                    buscaLargura(grafo, vertice);
                } else {
                    printf("Carregue o grafo primeiro.\n");
                }
                break;

            case 6: // Executar Bellman-Ford
                if (grafo != NULL) {
                    int vertice;
                    printf("Informe o vertice de partida para Bellman-Ford: ");
                    scanf("%d", &vertice);
                    printf("\nBellman-Ford a partir do vertice %d:\n", vertice);
                    bellmanFord(grafo, vertice);
                } else {
                    printf("Carregue o grafo primeiro.\n");
                }
                break;

            case 7: // Executar Componentes Conexas
                if (grafo != NULL) {
                    printf("\nComponentes Conexas:\n");
                    encontrarComponentesConexas(grafo);
                } else {
                    printf("Carregue o grafo primeiro.\n");
                }
                break;

            case 0: // Sair
                printf("Saindo...\n");
                if (grafo != NULL) {
                    liberarGrafo(grafo);
                }
                return 0;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}