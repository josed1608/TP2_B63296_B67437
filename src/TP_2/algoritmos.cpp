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

    R1a1<vert, int> rel;
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

    /*for(int deI = 0; deI < grafo.numVerts(); ++deI)
	{
		for(int aJ = deI+1; aJ < grafo.numVerts(); ++aJ)
		{
			imprimirCaminoFloyd(deI, aJ, mat, grafo, rel);
		}
    }*/

	imprimirMatrizFloyd(mat, grafo.numVerts(), grafo, rel);
}

void imprimirMatrizFloyd(int **mat, int nVerts, Grafo& grafo, R1a1<vert, int>& rel)
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

void copiar(Grafo &dest, Grafo &org)
{
    if(org.vacio()){
        return;
    }
    dest.vaciar();
    R1a1<vert, vert> rel;
    vert v = org.primerVert();
    while(v != vertNulo)
    {
        rel.agregarRel(v, dest.agregarVert(org.etiqueta(v)));
        v = org.steVert(v);
    }

    Dicc<Arista> aristasVist;
    v = org.primerVert();
    while(v != vertNulo)
    {
        vert vAdy = org.primerVertAdy(v);
        while(vAdy != vertNulo)
        {
            int peso = org.pesoArista(v, vAdy);
            Arista aAct = Arista(v,vAdy, peso);
            if(!aristasVist.pertenece(aAct))
            {
                dest.agregarArista(rel.imagen(v),rel.imagen(vAdy),peso);
                aristasVist.agregar(aAct);
            }
            vAdy = org.steVertAdy(v,vAdy);
        }
        v = org.steVert(v);
    }

}

bool iguales(Grafo &g1, Grafo &g2)
{
    if(g1.numVerts() != g2.numVerts() || g1.numAristas() != g2.numAristas()){
        return false;
    }

    //Veo si existen vertices con las mismas etiquetas
    R1a1<vert, vert> rel;
    vert v1 = g1.primerVert();
    while(v1 != vertNulo)
    {
        vert v2 = buscarVertice(g2, g1.etiqueta(v1));
        if(v2 == vertNulo)
        {
            return false;
        }
        rel.agregarRel(v1, v2);
        v1 = g1.steVert(v1);
    }

    //Ahora vero si existen las mismas aristas
    Dicc<Arista> aristasVist;
    vert v = g1.primerVert();
    while(v != vertNulo)
    {
        vert vAdy = g1.primerVertAdy(v);
        while(vAdy != vertNulo)
        {
            int peso = g1.pesoArista(v, vAdy);
            Arista aAct = Arista(v,vAdy, peso);
            if(!aristasVist.pertenece(aAct))
            {
                int peso2 = g2.pesoArista(rel.imagen(v), rel.imagen(vAdy));
                if(peso2 == -1 || peso2 != peso){
                    return false;
                }
                aristasVist.agregar(aAct);
            }
            vAdy = g1.steVertAdy(v,vAdy);
        }
        v = g1.steVert(v);
    }
    return true;
}

vert buscarVertice(Grafo& grafo, std::string etiq)
{
    vert vertice = grafo.primerVert();
    while(vertice != vertNulo && grafo.etiqueta(vertice) != etiq)
    {
        vertice = grafo.steVert(vertice);
    }
    return vertice;
}
