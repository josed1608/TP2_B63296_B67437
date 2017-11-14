#ifndef CONJUNTOD_H
#define CONJUNTOD_H

//#include "grafoLista.h"
#include "grafoMatriz.h"

#include<string>

class ConjuntoD
{
public:
	struct NodoElemento;

	struct NodoConjunto {
		std::string etiqueta;
		NodoConjunto * siguienteConjunto;
		NodoElemento * primerElem;
		NodoConjunto(std::string etiqueta, NodoConjunto * siguienteConjunto =nullptr, NodoElemento * primerElem= nullptr):
			etiqueta (etiqueta),
			siguienteConjunto(siguienteConjunto),
			primerElem(primerElem)
		{
		}
	};

	///@brief Nodo para la lista secundaria
	struct NodoElemento{
		vert vertice;
		NodoElemento * siguienteElemento;
		NodoElemento(vert vertice = vertNulo, NodoElemento * siguienteElemento=nullptr):
			vertice(vertice),
			siguienteElemento(siguienteElemento)
		{
		}
	};

public:
	NodoConjunto* primero;

public:
	ConjuntoD();

	~ConjuntoD();

	void vaciar();

	bool vacio();

	std::string conjuntoAlQuePertenece(vert elem);

	std::string agregarConjunto(std::string etiqueta, vert elem);

	std::string unirConjuntos(std::string c1, std::string c2);

};

#endif // CONJUNTOD_H
