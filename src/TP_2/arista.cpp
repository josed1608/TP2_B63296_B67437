#include "arista.h"

Arista::Arista(vert v1, vert v2, int peso):
	v1(v1),
	v2(v2),
	peso(peso)
{}

bool Arista::operator==(Arista arista)
{
	return (this->v1 == arista.v1 && this->v2 == arista.v2) || (this->v1 == arista.v2 && this->v2 == arista.v1);
}

bool Arista::operator!=(Arista arista)
{
	return !this->operator ==(arista);
}
