#ifndef ARISTA_H
#define ARISTA_H

//#include "grafoLista.h"
#include "grafoMatriz.h"

class Arista
{
public:
	vert v1;
	vert v2;
	int peso;

public:
	Arista(vert v1 = vertNulo, vert v2 = vertNulo, int peso = -1);

	bool operator==(Arista arista);

	bool operator!=(Arista arista);
};

#endif // ARISTA_H
