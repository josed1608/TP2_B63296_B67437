#ifndef R1A1_H
#define R1A1_H

#include <iostream>

#include "grafoLista.h"
//#include "grafoMatriz.h"

class R1a1
{
public:
	struct NodoLista
	{
		vert d;
		int c;
		NodoLista* siguiente;

		NodoLista(vert d, int c, NodoLista* siguiente = nullptr):
			d(d),
			c(c),
			siguiente(siguiente)
		{}
	};
	int n;
	NodoLista* primero;

public:
	//Iniciar
	R1a1();
	//Destruir
	~R1a1();

	void vaciar();

	inline bool vacio() {return n==0;}

	int imagen(vert d);

	vert preImagen(int c);

	bool estaDominio(vert d);

	bool estaCod(int c);

	void agregarRel(vert d, int c);

	void eliminarRel(vert d);

	inline int numElem() {return n;}

	void imprimirLista();
};

#endif // R1A1_H
