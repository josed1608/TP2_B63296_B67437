#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include <iostream>
#include <string>
#include <climits>
#include <iomanip>

#include "grafoLista.h"
//#include "grafoMatriz.h"
#include "colap.h"
#include "dicc.h"
#include "conjuntod.h"
#include "arista.h"
#include "r1a1.h"


void kruskal(Grafo& grafo);
void floyd(Grafo& grafo);
void imprimirMatrizFloyd(int** mat, int nVerts, Grafo &grafo, R1a1<vert, int> &rel);
void copiar(Grafo& dest, Grafo& org);
bool iguales(Grafo& g1, Grafo& g2);
vert buscarVertice(Grafo &grafo, std::string etiq);

#endif // ALGORITMOS_H
