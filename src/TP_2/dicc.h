#ifndef DICC_H
#define DICC_H

#include <iostream>

template <typename DataType> class Dicc
{
public:
	struct NodoLista
	{
		DataType elem;
		NodoLista* siguiente;

		NodoLista(DataType elem, NodoLista* siguiente = nullptr):
			elem(elem),
			siguiente(siguiente)
		{}
	};
	int n;
	NodoLista* primero;

public:
	//Iniciar
	Dicc();
	//Destruir
	~Dicc();

	void vaciar();

	inline bool vacio() {return n==0;}

	void agregar(DataType elem);

	void borrar(DataType elem);

	bool pertenece(DataType elem);

	inline int numElem() {return n;}

	void imprimirLista();
};

template<typename DataType>
Dicc<DataType>::Dicc():
	n(0),
	primero(nullptr)
{}

template<typename DataType>
Dicc<DataType>::~Dicc()
{
	this->vaciar();
}

template<typename DataType>
void Dicc<DataType>::vaciar()
{
	NodoLista* nodo = primero;
	while(nodo != nullptr){
		NodoLista* nodoABorrar = nodo;
		nodo = nodo->siguiente;
		delete nodoABorrar;
	}
	primero = nullptr;
	n = 0;
}

template<typename DataType>
void Dicc<DataType>::agregar(DataType elem)
{
	NodoLista* nodo = this->primero;
	while(nodo != nullptr && nodo->siguiente != nullptr && nodo->elem != elem)
	{
		nodo = nodo->siguiente;
	}
	if(nodo == nullptr)
	{
		this->primero = new NodoLista(elem);
	}
	else if(nodo->elem != elem)
	{
		nodo->siguiente = new NodoLista(elem);
	}
	this->n++;
}

template<typename DataType>
void Dicc<DataType>::borrar(DataType elem)
{
	NodoLista* nodoAdelante = this->primero;
	NodoLista* nodoAtras = nullptr;
	while(nodoAdelante != nullptr && nodoAdelante->siguiente != nullptr && nodoAdelante->elem != elem)
	{
		nodoAtras = nodoAdelante;
		nodoAdelante = nodoAdelante->siguiente;
	}
	if(nodoAdelante != nullptr && nodoAdelante->elem == elem)
	{
		if(nodoAtras != nullptr)
		{
			nodoAtras->siguiente = nodoAdelante->siguiente;
		}
		else
		{
			primero = nodoAdelante->siguiente;
			delete nodoAdelante;
		}
		this->n--;
	}
}

template<typename DataType>
bool Dicc<DataType>::pertenece(DataType elem)
{
	bool pertenece = false;
	NodoLista* nodo = this->primero;
	while(nodo != nullptr)
	{
		if(nodo->elem == elem)
		{
			pertenece = true;
		}
		nodo = nodo->siguiente;
	}
	return pertenece;
}

template<typename DataType>
void Dicc<DataType>::imprimirLista()
{
	NodoLista* nodo = this->primero;
	while(nodo != nullptr)
	{
		std::cout << nodo->elem << " ";
		nodo = nodo->siguiente;
	}
	std::cout << std::endl;
}


#endif // DICC_H
