#ifndef GRAPHVIZ
#define GRAPHVIZ

#include "grafo.h"

void gerarDOT(Grafo* grafo, const char* nomeArquivo);
void gerarImagemGrafo(const char* nomeArquivoDOT, const char* nomeImagem);

void gerarImagemDOT(const char* nomeDOT, const char* nomeImagem);

#endif