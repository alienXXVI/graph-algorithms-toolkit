# Algoritmos em Grafos

Este projeto implementa uma série de algoritmos clássicos em grafos, como busca em profundidade (DFS), busca em largura (BFS), Bellman-Ford, Kruskal, componentes conexas e componentes fortemente conexas. O programa também permite a visualização do grafo e das estruturas geradas pelos algoritmos, como a Árvore Geradora Mínima (AGM) e as componentes fortemente conexas.

<br>

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- **`grafo.h`**: Contém as definições das estruturas de dados e funções relacionadas à manipulação de grafos.
- **`algoritmos.h`**: Contém as definições das estruturas e funções para os algoritmos implementados.
- **`grafo.c`** e **`algoritmos.h`**: Contém as implementações das definições.
- **`main.c`**: Contém a função principal e o menu interativo para execução dos algoritmos.

<br>

## Funcionalidades

O programa oferece as seguintes funcionalidades:

1. **Carregar Grafo**: Carrega um grafo a partir de um arquivo de texto.
2. **Executar Kruskal**: Encontra a Árvore Geradora Mínima (AGM) usando o algoritmo de Kruskal.
3. **Executar Componentes Fortemente Conexas (CFC)**: Identifica e exibe as componentes fortemente conexas de um grafo direcionado.
4. **Executar Busca em Profundidade (DFS)**: Realiza uma busca em profundidade a partir de um vértice especificado.
5. **Executar Busca em Largura (BFS)**: Realiza uma busca em largura a partir de um vértice especificado.
6. **Executar Bellman-Ford**: Calcula os menores caminhos a partir de um vértice de origem usando o algoritmo de Bellman-Ford.
7. **Executar Componentes Conexas**: Identifica e exibe as componentes conexas de um grafo não direcionado.
8. **Desenhar Grafo**: Gera uma imagem do grafo usando a biblioteca Graphviz.
9. **Sair**: Encerra o programa.

<br>

## Compilar e Executar

### Pré-requisitos

- **Graphviz**: O projeto utiliza a biblioteca Graphviz para gerar visualizações dos grafos, deve estar instalada no sistema.
- **GCC**: Compilador C para compilar o código.

<br>

### Compilação

Para compilar o projeto, é utilizado o seguinte comando:

```bash
gcc -o main.exe sources/*.c main.c -I"C:\Program Files\Graphviz\include" -L"C:\Program Files\Graphviz\lib" -lcgraph -lgvc
```

Deve-se substituir o caminho "C:\Program Files\Graphviz\include" e "C:\Program Files\Graphviz\lib" pelos caminhos corretos da instalação do Graphviz no sistema.

<br>

### Execução

Após a compilação, é possível executar o programa com o comando:

```bash
.\main.exe
```

<br>

## Menu Interativo

O programa apresenta um menu interativo onde se pode escolher qual algoritmo executar. Basta seguir as instruções exibidas no console.

<br>

### Exemplo de Arquivo de Grafo
O grafo pode ser carregado a partir de um arquivo de texto com o seguinte formato:

```bash
orientado=sim
V=5
(0,1):11
(0,2):-4
(1,3):-5
(2,4):7
(3,0):2
(3,2):8
(4,2):19
```
<br>

### Visualização do Grafo
O programa gera arquivos DOT e imagens PNG para visualização do grafo e das estruturas geradas pelos algoritmos. As imagens são geradas usando a biblioteca Graphviz.

<br>
