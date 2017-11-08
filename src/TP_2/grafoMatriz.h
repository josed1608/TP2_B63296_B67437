#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include <string>
#define MAX 20 //tamaño máximo
#define PESONULL -1

typedef int peso;
typedef int vert;
extern vert vertNulo;

class Grafo
{
    //Desperdicio de la primera posicion
    std::string arrEtiq [MAX+1];
    // Matriz M*M
    // Vector para las aristas
    peso matPeso[MAX+1][MAX+1];
    // Puntero al ultimo, cantidad de vertices
    int n;

public:
	Grafo();

    void vaciar();

    inline bool vacio(){return (n==0)? true: false;}

    vert agregarVert(std::string e);

    void eliminarVert(vert v);

    inline void modificarEtiq(vert v, std::string e){arrEtiq[v]=e;}

    inline std::string etiqueta(vert v){return arrEtiq[v];}

    // Se le agrega el peso a ambos vertices. Como es un grafo dirigido para (v1, v2) y (v2, v1).
    void agregarArista(vert v1, vert v2, peso p ){ matPeso [v2][v1] =matPeso[v1][v2]= p;}

    // Se pone peso nulo a las a (v1, v2) y (v2, v1)
    void eliminarArista(vert v1, vert v2){ matPeso [v2][v1] =matPeso[v1][v2]= PESONULL;}

    // Como es un grafo no dirigido, se intercambia el peso para ambos (v1, v2) y (v2, v1)
    inline void modificarPeso(vert v1, vert v2, peso p){ matPeso [v2][v1] =matPeso[v1][v2]= p;}

    // Peso (v1, v2) = (v2, v1)
    inline peso pesoArista(vert v1, vert v2){return matPeso[v1][v2];}

    // Como no hay ciclos, no se incluye el caso de ser adyacente a uno mismo.
    inline bool adyacente(vert v1, vert v2){return (matPeso[v1][v2]>0)? true: false;}

    // Si no hay vertices, devuelve nulo. En caso contrario devuelve la primera posicion.
    inline vert primerVert(){return (n==0)? vertNulo: 1;}

    //Si la siguiente posicion si existe, la devuelve. Sino se le pasa una posicion nula.
    inline vert steVert(vert v){return (v+1<= n)? v+1: vertNulo;}

    vert primerVertAdy(vert v);

    vert steVertAdy(vert v, vert ady);

    inline int numVerts(){return n;}

    int numVertAdy(vert v);

    ~Grafo();
};

#endif // GRAFOMATRIZ_H
