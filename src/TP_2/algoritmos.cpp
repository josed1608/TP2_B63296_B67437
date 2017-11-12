#include "algoritmos.h"

void kruskal(Grafo &grafo)
{
	ColaP<Arista> aristas;
	ConjuntoD vertices;
	Dicc<Arista> visitadas;
	int aristasAgregadas = 0;
	int pesoTotal = 0;

	//Creo los subconjuntos y acomodo las aristas en la cola de prioridad
	vert v = grafo.primerVert();
	while(v != vertNulo)
	{
		vertices.agregarConjunto(grafo.etiqueta(v), v);
		vert vAdy = grafo.primerVertAdy(v);
		while(vAdy != vertNulo)
		{
			Arista actual = Arista(v, vAdy, grafo.pesoArista(v, vAdy));
			if(!visitadas.pertenece(actual))
			{
				aristas.agregar(actual, actual.peso);
				//std::cout << "arista: (" << actual.v1->etiqueta << ", " << actual.v2->etiqueta << ", " << actual.peso << ") agregada\n";
				visitadas.agregar(actual);
			}
			vAdy = grafo.steVertAdy(v, vAdy);
		}
		v = grafo.steVert(v);
	}

	while(!aristas.vacia() && aristasAgregadas != grafo.numVerts() - 1)
	{
		Arista actual = aristas.sacar();
		//std::cout << "analizando " << actual.v1->etiqueta << " " << actual.v2->etiqueta << std::endl;
		if(vertices.conjuntoAlQuePertenece(actual.v1) != vertices.conjuntoAlQuePertenece(actual.v2))
		{
			++aristasAgregadas;
			pesoTotal += actual.peso;
			std::cout << "La arista: (" << grafo.etiqueta(actual.v1) << ", " << grafo.etiqueta(actual.v2) << ") con peso " << actual.peso <<std::endl;
			vertices.unirConjuntos(vertices.conjuntoAlQuePertenece(actual.v1), vertices.conjuntoAlQuePertenece(actual.v2));
		}
	}
}

void floyd(Grafo& grafo)
{
	int** mat  = new int*[grafo.numVerts()];
	for(int i = 0; i<grafo.numVerts(); ++i)
	{
		mat[i] = new int[grafo.numVerts()];
	}

	for(int i = 0; i < grafo.numVerts(); ++i)
	{
		for(int j = 0; j < grafo.numVerts(); ++j)
		{
			if(i==j)
				mat[i][j] = 0;
			else
				mat[i][j] = INT_MAX;
		}
	}

	R1a1 rel;
	vert v = grafo.primerVert();
	int indice = 0;
	while(v != vertNulo)
	{
		rel.agregarRel(v,indice);
		++indice;
		v= grafo.steVert(v);
	}

	v = grafo.primerVert();
	while(v != vertNulo)
	{
		vert vAdy = grafo.primerVertAdy(v);
		while(vAdy != vertNulo)
		{
			mat[rel.imagen(v)][rel.imagen(vAdy)] = grafo.pesoArista(v, vAdy);
			vAdy = grafo.steVertAdy(v, vAdy);
		}
		v = grafo.steVert(v);
	}

	for(int k = 0; k < grafo.numVerts(); ++k)
	{
		for(int i = 0; i < grafo.numVerts(); ++i)
		{
			for(int j = 0; j < grafo.numVerts(); ++j)
			{
				if(mat[i][j] > mat[i][k] + mat[k][j])
					mat[i][j] = mat[i][k] + mat[k][j];
			}
		}
	}

	for(int deI = 0; deI < grafo.numVerts(); ++deI)
	{
		for(int aJ = deI+1; aJ < grafo.numVerts(); ++aJ)
		{
			imprimirCaminoFloyd(deI, aJ, mat, grafo, rel);
		}
	}

	imprimirMatrizFloyd(mat, grafo.numVerts(), grafo, rel);
}

void imprimirCaminoFloyd(int deI, int aJ, int** mat, Grafo& grafo, R1a1& rel)
{

}

void imprimirMatrizFloyd(int **mat, int nVerts, Grafo& grafo, R1a1& rel)
{
	std::cout << "La matriz resultante es:\n";

	std::cout << "     ";
	for(int deI = 0; deI < nVerts; ++deI)
	{
		std::cout << std::setw(5) << grafo.etiqueta(rel.preImagen(deI));
	}
	std::cout << std::endl;

	for(int deI = 0; deI < nVerts; ++deI)
	{
		std::cout << std::setw(5) << grafo.etiqueta(rel.preImagen(deI));
		for(int aJ = 0; aJ < nVerts; ++aJ)
		{
			std::cout << std::setw(5) << mat[deI][aJ];
		}
		std::cout <<std::endl;
	}
}
