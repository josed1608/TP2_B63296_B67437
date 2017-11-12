#include "r1a1.h"

R1a1::R1a1():
	n(0),
	primero(nullptr)
{}

R1a1::~R1a1()
{
	vaciar();
}

void R1a1::vaciar()
{
	while(primero != nullptr)
	{
		NodoLista* borrable = primero;
		primero = primero->siguiente;
		delete borrable;
	}
	n = 0;
}

int R1a1::imagen(vert d)
{
	NodoLista* rel = primero;
	while(rel != nullptr)
	{
		if(rel->d == d)
		{
			return rel->c;
		}
		rel = rel->siguiente;
	}
	return -1;
}

vert R1a1::preImagen(int c)
{
	NodoLista* rel = primero;
	while(rel != nullptr)
	{
		if(rel->c == c)
		{
			return rel->d;
		}
		rel = rel->siguiente;
	}
	return vertNulo;
}

bool R1a1::estaDominio(vert d)
{
	NodoLista* rel = primero;
	while (rel != nullptr)
	{
		if(rel->d == d)
		{
			return true;
		}
		rel = rel->siguiente;
	}
	return false;
}

bool R1a1::estaCod(int c)
{
	NodoLista* rel = primero;
	while(rel != nullptr)
	{
		if(rel->c == c)
		{
			return true;
		}
		rel = rel->siguiente;
	}
	return false;
}

void R1a1::agregarRel(vert d, int c)
{
	primero = new NodoLista(d,c,primero);
	++n;
}

void R1a1::eliminarRel(vert d)
{
	NodoLista* rel = primero;
	NodoLista* anterior = nullptr;
	bool borrado = false;
	while(rel!=nullptr && !borrado)
	{
		if(rel->d == d)
		{
			borrado = true;
		}
		else
		{
			anterior = rel;
			rel = rel->siguiente;
		}
	}
	if(borrado)
	{
		if(anterior == nullptr)
		{
			primero = primero->siguiente;
		}
		else
		{
			anterior->siguiente = rel->siguiente;
		}
		delete rel;
		--n;
	}
}

void R1a1::imprimirLista()
{
	NodoLista* rel = primero;
	while(rel != nullptr)
	{
		std::cout << rel->d << ", " << rel->c << std::endl;
		rel = rel->siguiente;
	}
}
