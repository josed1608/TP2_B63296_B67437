#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include <iostream>
#include <string>
#include <climits>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <fstream>

#include "colap.h"
#include "dicc.h"
#include "conjuntod.h"
#include "arista.h"
#include "r1a1.h"

#define INF INT_MAX
#define MAXARRAY 100
#define PEQ 5
#define MED 10
#define GRA 20
///Tiempos vendedor
#define PEQV 5
#define MEDV 10
#define GRAV 20

//Variables globales para el problema del vendedor
extern int solucAct [MAXARRAY];
extern Dicc<vert> diccG;
extern int mejorSol [MAXARRAY];
extern int minCosto;
extern int cantidadSol;
extern R1a1 <vert, int> relG;
extern int maxTamG;
extern int gananciaAct;


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
void vendedorR(Grafo &g, int i);
vert buscarVertice(Grafo &grafo, std::string etiq);
void imprimirDijkstra(Grafo &g,  vert v, vert *prev, int *dist, R1a1 <vert, int> &r);
void imprimirPrim(Grafo &g, vert *prev, int *weight, R1a1 <vert, int>& rel);
void limpiarVariablesGlobales();
void imprimirVendedor(Grafo &g);

/// Grafos especiales

/// Crea un grafo completo, osea que haya una arista entre cada vertice, excepto al vertice mismo como no tiene lazos
/// @param g Donde se va a crear el grafo
/// @param tam La cantidad de vertices que se desea crear.
void grafoCompleto(Grafo &g, int tam);

/// Crea un grafo que no tiene ninguna arista, los vertices estan aislados totalmente
/// @param g Donde se va a crear el grafo
/// @param tam La cantidad de vertices que se desea crear.
void grafoAislado(Grafo &g, int tam);


/// Tiempos
/// Imprime en el archivo los tiempos promedios de Dijkstra
/// @param Archivo donde imprime resultados
void tiempoDijkstra(std::ofstream archivo);
/// Imprime en el archivo los tiempos de Prim
/// @param Archivo donde imprime resultados
void tiemposPrim(std::ofstream& archivo);
/// Imprime en el archivo los tiempos de Vendedor, soluciones factibles y minCosto
/// @param Archivo donde imprime resultados
void tiemposVendedor(std::ofstream& archivo);

/// Obtiene el promedio de Dijsktra. Pide las e.d. necesarias para correr dijsktra.
std::chrono::duration<double> calcPromDij(Grafo & g, vert * prev, int * dist, R1a1 <vert, int> r);

#endif // ALGORITMOS_H
