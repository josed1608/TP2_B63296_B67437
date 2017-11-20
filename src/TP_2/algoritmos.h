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
/// Tama/os grafos
#define PEQ 100
#define MED 200
#define GRA 300
#define PEQ_ARI 200
#define MED_ARI 400
#define GRA_ARI 600
///Tama/os grafos vendedor
#define PEQV 8
#define MEDV 10
#define GRAV 12
#define PEQV_ARI 10
#define MEDV_ARI 20
#define GRAV_ARI 30

//Variables globales para el problema del vendedor
extern vert solucAct [MAXARRAY];
extern Dicc<vert> diccG;
extern vert mejorSol [MAXARRAY];
extern int minCosto;
extern int cantidadSol;
extern int maxTamG;
extern int gananciaAct;


//Grafos de prueba de tiempos
extern Grafo aisladoPeq;
extern Grafo aisladoMed;
extern Grafo aisladoGra;

extern Grafo completoPeq;
extern Grafo completoMed;
extern Grafo completoGra;

extern Grafo todAUnoPeq;
extern Grafo todAUnoMed;
extern Grafo todAUnoGra;

extern Grafo aleatorioPeq;
extern Grafo aleatorioMed;
extern Grafo aleatorioGra;


void kruskal(Grafo& grafo);

/**
 * @brief floyd Encuentra los caminos mas cortos entre todo par de vertices y los guarda en las matrices de pesos y previos
 * @param grafo Grafo al que se le encontraran los caminos
 * @param pesos Matriz para gurdar los pesos
 * @param prevs Matriz para guardar los vertices previos en los caminos
 * @param rel Relacion 1 a 1 entre vertices e indices para poder indexar las matrices
 */
void floyd(Grafo& grafo, int** pesos, vert** prevs, R1a1<vert, int>& rel);
/**
 * @brief imprimirMatrizFloyd Imprime la matriz de pesos de Floyd
 * @param mat Matriz de pesos
 * @param nVerts Cantidad de vertices
 * @param grafo Grafo al que corresponde la matriz
 * @param rel Relacion de verticesa a indices de la matriz
 */
void imprimirMatrizFloyd(int** mat, int nVerts, Grafo &grafo, R1a1<vert, int> &rel);
/**
 * @brief imprimirMatrizFloyd Imprime la matriz de previos de Floyd
 * @param mat Matriz de previos
 * @param nVerts Cantidad de vertices
 * @param grafo Grafo al que corresponde la matriz
 * @param rel Relacion de verticesa a indices de la matriz
 */
void imprimirMatrizPrevs(vert** mat, int nVerts, Grafo &grafo, R1a1<vert, int> &rel);
/**
 * @brief imprimirCaminoFloyd Imprime el camino más corto entre vInicio y vFinal
 * @param grafo Grafo donde estan los vertices
 * @param vInicio vertice de salida
 * @param vFinal vertice de llegada
 * @param pesos Matriz de pesos
 * @param prevs Matriz de previos
 * @param rel Relacion de vertices a indices de la matriz
 */
void imprimirCaminoFloyd(Grafo& grafo, vert vInicio, vert vFinal, int** pesos, vert** prevs, R1a1<vert, int>& rel);

/**
 * @brief copiar Copia en dest el grafo org
 * @param dest Grafo de destino
 * @param org Grafo de origen
 */
void copiar(Grafo& dest, Grafo& org);

/**
 * @brief iguales Indica si g1 es igual a g2
 * @param g1 grafo 1
 * @param g2 grafo 2
 * @return Bool que indica si son o no iguales
 */
bool iguales(Grafo& g1, Grafo& g2);

void dijkstra(Grafo &g, vert v, vert * prev, int * dist , R1a1<vert, int>& r);
void imprimirDijkstra(Grafo &g,  vert v, vert *prev, int *dist, R1a1 <vert, int> &r);

void prim(Grafo & g, vert *prev, int *weight, R1a1 <vert, int>& rel);
void imprimirPrim(Grafo &g, vert *prev, int *weight, R1a1 <vert, int>& rel);

void vendedor(Grafo &g);
void vendedorR(Grafo &g, int i);
void imprimirVendedor(Grafo &g);

/**
 * @brief buscarVertice Busca el vertice en el grafo con la etiqueta etiq
 * @param grafo Grafo donde se busca
 * @param etiq Etiqueta que se busca
 * @return Devuelve el vertice si lo encontró o vertNulo si no
 */
vert buscarVertice(Grafo &grafo, std::string etiq);

void limpiarVariablesGlobales();

/// Grafos especiales
/**
 * @brief crearGrafosTiempos Carga todos los grafos globles con los que se miden los tiempos
 */
void crearGrafosTiempos();

/**
 * @brief limpiarGrafosTiempos Vacia los grafos globales para medir tiempos
 */
void limpiarGrafosTiempos();

/// Crea un grafo completo, osea que haya una arista entre cada vertice, excepto al vertice mismo como no tiene lazos
/// @param g Donde se va a crear el grafo
/// @param tam La cantidad de vertices que se desea crear.
void grafoCompleto(Grafo &g, int tam);

/// Crea un grafo que no tiene ninguna arista, los vertices estan aislados totalmente
/// @param g Donde se va a crear el grafo
/// @param tam La cantidad de vertices que se desea crear.
void grafoAislado(Grafo &g, int tam);

/**
 * @brief grafoTodosAUno Crea un grafo donde un vértice está conectado a todos los demás pero el resto solo están conectados al principal
 * @param g Donde se va a crear el grafo
 * @param tam La cantidad de vertices
 */
void grafoTodosAUno(Grafo& g, int tam);

/**
 * @brief grafoAleatorio Crea un grafo con la cantidad de vertices y aristas especificadas donde las aristas son colocadas de forma aleatoria. Además el grafo resultante siempre es conexo mientras  aristas>=vertices-1
 * @param g Donde se va a crear el grafo
 * @param verts Cantidad de vertices
 * @param aristas cantidad de aristas
 */
void grafoAleatorio(Grafo& g, int verts, int aristas);

/// Tiempos
/// Imprime en el archivo los tiempos promedios de Dijkstra
/// @param Archivo donde imprime resultados
void tiempoDijkstra(std::ofstream& archivo);

/**
 * @brief tiemposFloyd Imprime en el archivo los tiempos de ejecutar Floyd
 * @param archivo Donde imprime los resultados
 */
void tiemposFloyd(std::ofstream& archivo);

/// Imprime en el archivo los tiempos de Prim
/// @param Archivo donde imprime resultados
void tiemposPrim(std::ofstream& archivo);

/**
 * @brief tiemposKruskal Imprime en el archivo los tiempos de ejecutar Kruskal
 * @param archivo Donde imprime los resultados
 */
void tiemposKruskal(std::ofstream& archivo);

/// Imprime en el archivo los tiempos de Vendedor, soluciones factibles y minCosto
/// @param Archivo donde imprime resultados
void tiemposVendedor(std::ofstream& archivo);

/// Obtiene el promedio de Dijsktra. Pide las e.d. necesarias para correr dijsktra.
std::chrono::duration<double> calcPromDij(Grafo & g, vert * prev, int * dist, R1a1 <vert, int> r);

#endif // ALGORITMOS_H
