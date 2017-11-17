#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include <iostream>
#include <string>
#include <climits>
#include <iomanip>

#include "colap.h"
#include "dicc.h"
#include "conjuntod.h"
#include "arista.h"
#include "r1a1.h"


void kruskal(Grafo& grafo);
void floyd(Grafo& grafo, int** pesos, vert** prevs, R1a1<vert, int> rel);
void imprimirMatrizFloyd(int** mat, int nVerts, Grafo &grafo, R1a1<vert, int> &rel);
void imprimirMatrizPrevs(vert** mat, int nVerts, Grafo &grafo, R1a1<vert, int> &rel);
void imprimirCaminoFloyd(Grafo& grafo, vert vInicio, vert vFinal, int** pesos, vert** prevs);
void copiar(Grafo& dest, Grafo& org);
bool iguales(Grafo& g1, Grafo& g2);
void dijkstra(Grafo &g, vert v, vert * prev, int * dist , R1a1<vert, int>& r);
void prim(Grafo & g, vert *prev, int *weight, R1a1 <vert, int>& rel);
void vendedor(Grafo &g);
vert buscarVertice(Grafo &grafo, std::string etiq);
void imprimirDijkstra(Grafo &g,  vert v, vert *prev, int *dist, R1a1 <vert, int> &r);
void imprimirPrim(Grafo &g, vert *prev, int *weight, R1a1 <vert, int>& rel);

#endif // ALGORITMOS_H
