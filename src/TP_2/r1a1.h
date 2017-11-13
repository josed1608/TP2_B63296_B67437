#ifndef R1A1_H
#define R1A1_H

#include <iostream>

template <typename Dominio, typename Codominio>
class R1a1
{
public:
	struct NodoLista
	{
        Dominio d;
        Codominio c;
		NodoLista* siguiente;

        NodoLista(Dominio d, Codominio c, NodoLista* siguiente = nullptr):
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

    Codominio imagen(Dominio d);

    Dominio preImagen(Codominio c);

    bool estaDominio(Dominio d);

    bool estaCod(Codominio c);

    void agregarRel(Dominio d, Codominio c);

    void eliminarRel(Dominio d);

	inline int numElem() {return n;}

	void imprimirLista();
};

template <typename Dominio, typename Codominio>
R1a1<Dominio, Codominio>::R1a1():
    n(0),
    primero(nullptr)
{}

template <typename Dominio, typename Codominio>
R1a1<Dominio, Codominio>::~R1a1()
{
    vaciar();
}

template <typename Dominio, typename Codominio>
void R1a1<Dominio, Codominio>::vaciar()
{
    while(primero != nullptr)
    {
        NodoLista* borrable = primero;
        primero = primero->siguiente;
        delete borrable;
    }
    n = 0;
}

template <typename Dominio, typename Codominio>
Codominio R1a1<Dominio, Codominio>::imagen(Dominio d)
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
    return Codominio();
}

template <typename Dominio, typename Codominio>
Dominio R1a1<Dominio, Codominio>::preImagen(Codominio c)
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
    return Dominio();
}

template <typename Dominio, typename Codominio>
bool R1a1<Dominio, Codominio>::estaDominio(Dominio d)
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

template <typename Dominio, typename Codominio>
bool R1a1<Dominio, Codominio>::estaCod(Codominio c)
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

template <typename Dominio, typename Codominio>
void R1a1<Dominio, Codominio>::agregarRel(Dominio d, Codominio c)
{
    primero = new NodoLista(d,c,primero);
    ++n;
}

template <typename Dominio, typename Codominio>
void R1a1<Dominio, Codominio>::eliminarRel(Dominio d)
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

template <typename Dominio, typename Codominio>
void R1a1<Dominio, Codominio>::imprimirLista()
{
    NodoLista* rel = primero;
    while(rel != nullptr)
    {
        std::cout << rel->d << ", " << rel->c << std::endl;
        rel = rel->siguiente;
    }
}
#endif // R1A1_H
