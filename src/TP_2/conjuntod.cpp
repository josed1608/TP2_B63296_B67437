#include "conjuntod.h"

ConjuntoD::ConjuntoD():
	primero(nullptr)
{}

ConjuntoD::~ConjuntoD()
{
	vaciar();
}

void ConjuntoD::vaciar()
{
	NodoConjunto* c = primero;
	while(c != nullptr)
	{
		NodoElemento* e = c->primerElem;
		while(e != nullptr)
		{
			NodoElemento* borrable = e;
			e = e->siguienteElemento;
			delete borrable;
		}
		NodoConjunto* borrable = c;
		c = c->siguienteConjunto;
		delete borrable;
	}
}

bool ConjuntoD::vacio()
{
	return (primero == nullptr);
}

#include <iostream>

std::string ConjuntoD::conjuntoAlQuePertenece(vert elem)
{
	NodoConjunto* c = primero;
	while(c != nullptr)
	{
		NodoElemento* e = c->primerElem;
		while(e != nullptr)
		{
			if(e->vertice == elem)
			{
				return c->etiqueta;
			}
			e = e->siguienteElemento;
		}
		c = c->siguienteConjunto;
	}
	return std::string();
}

std::string ConjuntoD::agregarConjunto(std::string etiqueta, vert elem)
{
	primero = new NodoConjunto(etiqueta, primero, new NodoElemento(elem));
	return etiqueta;
}

std::string ConjuntoD::unirConjuntos(std::string c1, std::string c2)
{
	//Encuentro los conjuntos en la lista principal
	NodoConjunto* conjunto1 = primero;
	NodoConjunto* conjunto2 = primero;
	NodoConjunto* anteriorC2 = nullptr; //para borrar a conjunto2
	bool c1Encontrado = false, c2Encontrado = false;
	while(!c1Encontrado || !c2Encontrado)
	{
		if(conjunto1->etiqueta == c1)
		{
			c1Encontrado = true;
		}
		if(conjunto2->etiqueta == c2)
		{
			c2Encontrado = true;
		}

		if(c1Encontrado && !c2Encontrado)
		{
			anteriorC2 = conjunto2;
			conjunto2 = conjunto2->siguienteConjunto;
		}
		else if(c2Encontrado && !c1Encontrado)
		{
			conjunto1 = conjunto1->siguienteConjunto;
		}
		else if (!c1Encontrado && !c2Encontrado)
		{
			anteriorC2 = conjunto2;
			conjunto2 = conjunto2->siguienteConjunto;
			conjunto1 = conjunto1->siguienteConjunto;
		}
	}

	//Copio la lista del segundo conjunto en el primero
	NodoElemento* elem2 = conjunto2->primerElem;
	while(elem2 != nullptr)
	{
		NodoElemento* temp = elem2->siguienteElemento;
		elem2->siguienteElemento = conjunto1->primerElem;
		conjunto1->primerElem = elem2;
		elem2 = temp;
	}

	//Borro a c2 de la lista principal
	if(anteriorC2 == nullptr)
	{
		primero = primero->siguienteConjunto;
	}
	else
	{
		anteriorC2->siguienteConjunto = conjunto2->siguienteConjunto;
	}
	delete conjunto2;

	//std::cout << "Siguiente a primero " << primero->siguienteConjunto->etiqueta << std::endl;

	//std::cout << "final: " << conjunto1->etiqueta << std::endl;
	return conjunto1->etiqueta;
}
