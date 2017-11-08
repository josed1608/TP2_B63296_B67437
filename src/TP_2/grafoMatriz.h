#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include <string>
#define MAX 100 //tamaño máximo

typedef int peso;
typedef int vert;
extern vert vertNulo;

class Grafo
{
    //Desperdicio de la primera posicion
    std::string arrayEtiq [MAX+1];


public:
	Grafo();

    void vaciar();

    bool vacio();

    vert agregarVert(std::string e);

    void eliminarVert(vert v);

    void modificarEtiq(vert v, std::string e);

    std::string etiqueta(vert v);

    void agregarArista(vert v1, vert v2, peso p );

    void eliminarArista(vert v1, vert v2);

    void modificarPeso(vert v1, vert v2, peso p);

    peso pesoArista(vert v1, vert v2);

    bool adyacente(vert v1, vert v2);

    vert primerVert();

    vert steVert(vert v);

    vert primerVertAdy(vert v);

    vert steVertAdy(vert v, vert ady);

    int numVerts();

    int numVertAdy(vert v);

    ~Grafo();
};

#endif // GRAFOMATRIZ_H
