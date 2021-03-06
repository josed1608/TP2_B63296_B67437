#include "grafoLista.h"

vert vertNulo = nullptr;

Grafo::Grafo():
	nVerts(0),
	nAristas(0),
	primero(nullptr)
{}

Grafo::~Grafo()
{
	this->vaciar();
}

void Grafo::vaciar()
{
    vert vertice = primero;
	while(vertice != nullptr)
	{
		NodoSecundario* arista = vertice->primerAdy;
		while(arista != nullptr)
		{
			NodoSecundario* borrable = arista;
			arista = arista->siguienteAdy;
			delete borrable;
		}
        vert borrable = vertice;
		vertice = vertice->siguienteVert;
		delete borrable;
	}
    nVerts = 0;
    nAristas = 0;
    primero = nullptr;
}

NodoPrincipal *Grafo::agregarVert(std::string etiq)
{
	primero = new NodoPrincipal(etiq, primero);
	nVerts++;
	return primero;
}

void Grafo::agregarArista(vert v1, vert v2, int peso)
{
	v1->primerAdy = new NodoSecundario(peso, v2, v1->primerAdy);
	v2->primerAdy = new NodoSecundario(peso, v1, v2->primerAdy);
	nAristas++;
}

void Grafo::modificarPeso(vert v1,vert v2, int peso)
{
	NodoSecundario* arista = v1->primerAdy;
	while(arista != nullptr && arista->refListaPrincipal != v2)
	{
		arista = arista->siguienteAdy;
	}
	arista->peso = peso;

	arista = v2->primerAdy;
	while(arista != nullptr && arista->refListaPrincipal != v1)
	{
		arista = arista->siguienteAdy;
	}
	arista->peso = peso;
}

void Grafo::eliminarVert(vert v)
{
	if(primero == v)
	{
		primero = primero->siguienteVert;
	}
	else
	{
        vert vertice = primero;
		while(vertice->siguienteVert != v)
		{
			vertice = vertice->siguienteVert;
		}
		vertice->siguienteVert = v->siguienteVert;
	}
	delete v;
	nVerts--;
}

void Grafo::eliminarArista(vert v1, vert v2)
{
	if(v1->primerAdy->refListaPrincipal == v2)
	{
		NodoSecundario* borrable = v1->primerAdy;
		v1->primerAdy = v1->primerAdy->siguienteAdy;
		delete borrable;
	}
	else
	{
		NodoSecundario* arista = v1->primerAdy;
		while(arista != nullptr && arista->siguienteAdy->refListaPrincipal != v2)
		{
			arista = arista->siguienteAdy;
		}
		NodoSecundario* borrable = arista->siguienteAdy;
		arista->siguienteAdy = arista->siguienteAdy->siguienteAdy;
		delete borrable;
	}

	if(v2->primerAdy->refListaPrincipal == v1)
	{
		NodoSecundario* borrable = v2->primerAdy;
		v2->primerAdy = v2->primerAdy->siguienteAdy;
		delete borrable;
	}
	else
	{
		NodoSecundario* arista = v2->primerAdy;
		while(arista != nullptr && arista->siguienteAdy->refListaPrincipal != v1)
		{
			arista = arista->siguienteAdy;
		}
		NodoSecundario* borrable = arista->siguienteAdy;
		arista->siguienteAdy = arista->siguienteAdy->siguienteAdy;
		delete borrable;
	}
	nAristas--;
}

void Grafo::modificarEtiq(vert v, std::string etiq)
{
	v->etiqueta = etiq;
}

int Grafo::numVertAdy(vert v)
{
	int contador = 0;
	NodoSecundario* arista = v->primerAdy;
	while(arista != nullptr)
	{
		++contador;
		arista = arista->siguienteAdy;
	}
	return contador;
}

bool Grafo::adyacente(vert v1, vert v2)
{
	NodoSecundario* arista = v1->primerAdy;
	while(arista != nullptr)
	{
		if(arista->refListaPrincipal == v2)
		{
			return true;
		}
		arista = arista->siguienteAdy;
	}
	return false;
}

int Grafo::pesoArista(vert v1, vert v2)
{
	NodoSecundario* arista = v1->primerAdy;
	while(arista != nullptr && arista->refListaPrincipal != v2)
	{
		arista = arista->siguienteAdy;
	}
    if(arista != nullptr)
        return arista->peso;
    return -1;
}

NodoPrincipal *Grafo::steVertAdy(vert deV1, vert trasV2)
{
	NodoSecundario* arista = deV1->primerAdy;
	while(arista != nullptr && arista->refListaPrincipal != trasV2)
	{
		arista = arista->siguienteAdy;
	}
	return arista->siguienteAdy != nullptr ? arista->siguienteAdy->refListaPrincipal : nullptr;
}
