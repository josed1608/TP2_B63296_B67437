#include "grafoMatriz.h"

vert vertNulo = -1;

Grafo::Grafo()
{

}


void Grafo::vaciar()
{

}

bool Grafo::vacio()
{
    return true;
}

vert Grafo::agregarVert(std::string e)
{
    return 1;
}

void Grafo::eliminarVert(vert v)
{

}

void Grafo::modificarEtiq(vert v, std::string e)
{

}

std::string Grafo::etiqueta(vert v)
{
    return "nel";
}

void Grafo::agregarArista(vert v1, vert v2, peso p )
{

}

void Grafo::eliminarArista(vert v1, vert v2)
{

}

void Grafo::modificarPeso(vert v1, vert v2, peso p)
{

}

peso Grafo::pesoArista(vert v1, vert v2)
{
    return 0;
}

bool Grafo::adyacente(vert v1, vert v2)
{
    return false;
}

vert Grafo::primerVert()
{
    return 0;
}

vert Grafo::steVert(vert v)
{
    return 0;
}

vert Grafo::primerVertAdy(vert v)
{
    return 0;
}

vert Grafo::steVertAdy(vert v, vert ady)
{
    return 0;
}

int Grafo::numVerts()
{
    return 0;
}

int Grafo::numVertAdy(vert v)
{
    return 0;
}

Grafo::~Grafo()
{

}
