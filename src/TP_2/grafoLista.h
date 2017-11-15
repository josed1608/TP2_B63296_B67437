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
    vert primero;

public:
	Grafo();

	~Grafo();

	void vaciar();

	inline bool vacio() {return nVerts==0;}

    vert agregarVert(std::string etiq);

    void agregarArista(vert v1, vert v2, int peso);

    void modificarPeso(vert v1, vert v2, int peso);

    void eliminarVert(vert v);

    void eliminarArista(vert v1, vert v2);

    void modificarEtiq(vert v, std::string etiq);

    inline int numAristas() {return nAristas;}

	inline int numVerts() {return nVerts;}

	int numVertAdy(vert v);

    bool adyacente(vert v1, vert v2);

    inline std::string etiqueta(vert v) {return v->etiqueta;}

    int pesoArista(vert v1, vert v2);

	inline vert primerVertAdy(vert v) {return v->primerAdy == nullptr ? nullptr : v->primerAdy->refListaPrincipal;}

    vert steVertAdy(vert deV1, vert trasV2);

    inline vert primerVert() {return primero;}

    inline vert steVert(vert trasV) {return trasV->siguienteVert;}
};

#endif // GRAFOLISTA_H
