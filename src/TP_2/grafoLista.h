#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include <string>

struct NodoSecundario;

///@brief Nodo para la lista principal
struct NodoPrincipal {
	std::string etiqueta;
	NodoPrincipal * siguienteVert;
	NodoSecundario * primerAdy;
	NodoPrincipal(std::string etiqueta, NodoPrincipal * siguienteVert =nullptr, NodoSecundario * primerAdy= nullptr):
		etiqueta (etiqueta),
		siguienteVert(siguienteVert),
		primerAdy(primerAdy)
	{
	}
};

///@brief Nodo para la lista secundaria
struct NodoSecundario{
	NodoPrincipal * refListaPrincipal;
	NodoSecundario * siguienteAdy;
	int peso;
	NodoSecundario(NodoPrincipal * refListaPrincipal= nullptr, NodoSecundario * siguienteAdy=nullptr, int peso = 0):
		refListaPrincipal(refListaPrincipal),
		siguienteAdy(siguienteAdy),
		peso(peso)
	{
	}

};

typedef NodoPrincipal* vert;
extern vert vertNulo;

class Grafo
{
public:
	Grafo();
};

#endif // GRAFOLISTA_H
