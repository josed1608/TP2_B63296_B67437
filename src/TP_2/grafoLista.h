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
	int peso;
	NodoPrincipal * refListaPrincipal;
	NodoSecundario * siguienteAdy;
	NodoSecundario(int peso = 0, NodoPrincipal * refListaPrincipal= nullptr, NodoSecundario * siguienteAdy=nullptr):
		peso(peso),
		refListaPrincipal(refListaPrincipal),
		siguienteAdy(siguienteAdy)
	{
	}

};

typedef NodoPrincipal* vert;
extern vert vertNulo;

class Grafo
{
public:
	int nVerts;
	int nAristas;
	NodoPrincipal* primero;

public:
	Grafo();

	~Grafo();

	void vaciar();

	inline bool vacio() {return nVerts==0;}

	NodoPrincipal* agregarVert(std::string etiq);

	void agregarArista(NodoPrincipal* v1, NodoPrincipal* v2, int peso);

	void modificarPeso(NodoPrincipal* v1, NodoPrincipal* v2, int peso);

	void eliminarVert(NodoPrincipal* v);

	void eliminarArista(NodoPrincipal* v1, NodoPrincipal* v2);

	void modificarEtiq(NodoPrincipal* v, std::string etiq);

	inline int numAristas() {return nAristas;}

	inline int numVerts() {return nVerts;}

	int numAristasSalida(NodoPrincipal* v);

	bool estaAislado(NodoPrincipal* v);

	inline std::string etiqueta(NodoPrincipal* v) {return v->etiqueta;}

	int pesoArista(NodoPrincipal* v1, NodoPrincipal* v2);

	inline NodoPrincipal* primerVertAdy(NodoPrincipal* v) {return v->primerAdy->refListaPrincipal;}

	NodoPrincipal* steVertAdy(NodoPrincipal* deV1, NodoPrincipal* trasV2);

	inline NodoPrincipal* primerVert() {return primero;}

	inline NodoPrincipal* steVert(NodoPrincipal* trasV) {return trasV->siguienteVert;}
};

#endif // GRAFOLISTA_H
