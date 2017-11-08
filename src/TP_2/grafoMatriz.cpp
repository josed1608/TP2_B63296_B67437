#include "grafoMatriz.h"

vert vertNulo = -1;

Grafo::Grafo()
: n{0}
{
}


void Grafo::vaciar()
{
    // Pone que el puntero al ultimo es 0
    n=0;
}


vert Grafo::agregarVert(std::string e)
{
    ++n;
    arrEtiq[n] =e;
    // Coloca que no tiene aristas con los demas vertices
    for(int i =1; i< n;++i)
    {
        matPeso[n][i]= matPeso[i][n] = PESONULL;
    }
    //Se pone como el peso en la diagonal de posicion un 0
    matPeso[n][n]= 0;
    return n;
}

void Grafo::eliminarVert(vert v)
{

}

vert Grafo::primerVertAdy(vert v)
{
    for(int i =1; i<=n; ++i)
    {
        //Si se encuentra algo que no sea ni peso nulo ni el mismo(0), significa que hay arista.
        if(matPeso[v][i]>0)
            return i;
    }
    return vertNulo;
}

vert Grafo::steVertAdy(vert v, vert ady)
{
    for(int i =ady+1; i<=n;++i )
    {
        //Si se encuentra algo que no sea ni peso nulo ni el mismo(0), significa que hay arista.
        if(matPeso[v][i]>0)
            return i;
    }
    return vertNulo;
}

int Grafo::numVertAdy(vert v)
{
    int total =0;
    for(int i =1; i<=n; ++i)
    {
        //Si se encuentra algo que no sea ni peso nulo ni el mismo(0), significa que hay arista.
        if(matPeso[v][i] >0)
           ++total;
    }
    return total;
}

Grafo::~Grafo()
{
}
