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
    for(int i =1; i<= n;++i)
    {
        matPeso[n][i]= matPeso[i][n] = PESONULL;
    }
    return n;
}

void Grafo::eliminarVert(vert v)
{
    //mueve hasta llegar al final en el vector de etiquetas
    for(int i=v+1; i<=n ;++i)
    {
        arrEtiq[i-1] = arrEtiq[i];
    }
    // Mueve toda las matriz de pesos
    for(int i= v+1, j=1; i <=n ; ++i)
    {
        //mueve la columna
        for(j=1; j<=n; ++j)
        {
            matPeso[i-1][j] = matPeso[i][j];
        }
        //mueve la fila
        for(j=1; j<=n; ++j)
        {
            matPeso[j][i-1] = matPeso[j][i];
        }
    }
    --n;
}

vert Grafo::primerVertAdy(vert v)
{
    for(int i =1; i<=n; ++i)
    {
        //Si se encuentra algo que no sea ni peso nulo ni el mismo(0), significa que hay arista.
        if(matPeso[v][i]!= vertNulo)
            return i;
    }
    return vertNulo;
}

vert Grafo::steVertAdy(vert v, vert ady)
{
    for(int i =ady+1; i<=n;++i )
    {
        //Si se encuentra algo que no sea ni peso nulo ni el mismo(0), significa que hay arista.
        if(matPeso[v][i]!= vertNulo)
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
        if(matPeso[v][i] !=vertNulo)
           ++total;
    }
    return total;
}

Grafo::~Grafo()
{
}
