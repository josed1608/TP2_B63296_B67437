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
				visitadas.agregar(actual);
			}
			vAdy = grafo.steVertAdy(v, vAdy);
		}
		v = grafo.steVert(v);
	}

	while(!aristas.vacia() && aristasAgregadas != grafo.numVerts() - 1)
	{
		Arista actual = aristas.sacar();
		if(vertices.conjuntoAlQuePertenece(actual.v1) != vertices.conjuntoAlQuePertenece(actual.v2))
		{
			++aristasAgregadas;
			pesoTotal += actual.peso;
			std::cout << "La arista: (" << grafo.etiqueta(actual.v1) << ", " << grafo.etiqueta(actual.v2) << ") con peso " << actual.peso <<std::endl;
			vertices.unirConjuntos(vertices.conjuntoAlQuePertenece(actual.v1), vertices.conjuntoAlQuePertenece(actual.v2));
		}
	}
}

void floyd(Grafo& grafo, int **pesos, vert **prevs, R1a1<vert, int> rel)
{
	for(int i = 0; i < grafo.numVerts(); ++i)
	{
		for(int j = 0; j < grafo.numVerts(); ++j)
		{
			if(i==j)
				pesos[i][j] = 0;
			else
				pesos[i][j] = INF;
			prevs[i][j] = vertNulo;
		}
	}

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
			pesos[rel.imagen(v)][rel.imagen(vAdy)] = grafo.pesoArista(v, vAdy);
			prevs[rel.imagen(v)][rel.imagen(vAdy)] = vAdy;
			vAdy = grafo.steVertAdy(v, vAdy);
		}
		v = grafo.steVert(v);
	}

	int n = grafo.numVerts();
	for(int k = 0; k < n; ++k)
	{
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				if(pesos[i][k] != INF && pesos[k][j] != INF)
				{
					if(pesos[i][j] > pesos[i][k] + pesos[k][j])
					{
						pesos[i][j] = pesos[i][k] + pesos[k][j];
						prevs[i][j] = prevs[i][k];
					}
				}
			}
		}
	}

	//imprimirMatrizFloyd(pesos, grafo.numVerts(), grafo, rel);
	//imprimirMatrizPrevs(prevs, grafo.numVerts(), grafo, rel);
}

void imprimirMatrizPrevs(vert** mat, int nVerts, Grafo &grafo, R1a1<vert, int> &rel){
	std::cout << "La matriz resultante es:\n";

	std::cout << "     ";
	for(int deI = 0; deI < nVerts; ++deI)
	{
		std::cout << std::setw(10) << grafo.etiqueta(rel.preImagen(deI));
	}
	std::cout << std::endl;

	for(int deI = 0; deI < nVerts; ++deI)
	{
		std::cout << std::setw(10) << grafo.etiqueta(rel.preImagen(deI));
		for(int aJ = 0; aJ < nVerts; ++aJ)
		{
			std::cout << std::setw(10) << mat[deI][aJ];
		}
		std::cout <<std::endl;
	}
}

void imprimirCaminoFloyd(Grafo &grafo, vert vInicio, vert vFinal, int **pesos, vert **prevs)
{
	R1a1<vert, int> rel;
	vert v = grafo.primerVert();
	int indice = 0;
	while(v != vertNulo)
	{
		rel.agregarRel(v,indice);
		++indice;
		v= grafo.steVert(v);
	}

	if(prevs[rel.imagen(vInicio)][rel.imagen(vFinal)] == vertNulo)
	{
		std::cout << "No hay camino\n";
	}
	else
	{
		std::cout << "El camino mas corto posee un peso de: " << pesos[rel.imagen(vInicio)][rel.imagen(vFinal)] << std::endl;
		std::cout << "Y esta dado por el camino: \n" << grafo.etiqueta(vInicio);
		while(vInicio != vFinal)
		{
			std::cout << ", ";
			vInicio = prevs[rel.imagen(vInicio)][rel.imagen(vFinal)];
			std::cout << grafo.etiqueta(vInicio);
		}
		std::cout <<std::endl;
	}
}

void imprimirMatrizFloyd(int **mat, int nVerts, Grafo& grafo, R1a1<vert, int>& rel)
{
	std::cout << "La matriz resultante es:\n";

	std::cout << "     ";
	for(int deI = 0; deI < nVerts; ++deI)
	{
		std::cout << std::setw(10) << grafo.etiqueta(rel.preImagen(deI));
	}
	std::cout << std::endl;

	for(int deI = 0; deI < nVerts; ++deI)
	{
		std::cout << std::setw(10) << grafo.etiqueta(rel.preImagen(deI));
		for(int aJ = 0; aJ < nVerts; ++aJ)
		{
			std::cout << std::setw(10) << mat[deI][aJ];
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

void dijkstra(Grafo &g, vert v, vert *prev, int *dist , R1a1 <vert, int>& r)
{
    int tamG =g.numVerts(), pMen, cPes, iAct;
    vert vAct = g.primerVert(), vTemp, vMen;
    Dicc <vert> d;

    for(int index =0; index < tamG; ++index)
    {
        // Dejar en peso lo maximo
        dist[index] = INF;
        // Dejar como anterior vacio
        prev[index] = vertNulo;
        // Hacer la relacion con el vertice y la posicion de indice
        r.agregarRel(vAct, index);
        vAct = g.steVert(vAct);
    }
    //Peso para el primer vertice es 0
    dist [r.imagen(v)] =0;
    for(int tam = tamG; tam !=0 ; --tam)
    {
        pMen= INT_MAX;
        //Coger el vertice mas peque/o no visitado
        for(int index =0; index<tamG; ++index )
        {
            if(pMen > dist[index] && !d.pertenece(vTemp =r.preImagen(index)))
            {
                pMen = dist[index];
                vMen = vTemp;
            }
        }
        d.agregar(vMen);
        // Ver si existe un camino mas corto. Ignora los que tienen infinito.
        if(pMen != INF)
        {
            for (vert hijoAct=g.primerVertAdy(vMen); hijoAct!=vertNulo ; hijoAct = g.steVertAdy(vMen, hijoAct))
            {
                // Si existe un camino mas corto, actualizar el anterior y la distancia
                if((cPes = pMen + g.pesoArista( vMen,hijoAct )) < dist[iAct = r.imagen(hijoAct)])
                {
                    dist[iAct] = cPes;
                    prev[iAct] = vMen;
                }
            }
        }
    }
}


void prim(Grafo &g, vert *prev, int *weight, R1a1 <vert, int>& rel )
{
    int tamG = g.numVerts(), pMen;
    Dicc <vert> d;
    vert vAct =g.primerVert(), vTemp;
    for(int index=0; index < tamG; ++index)
    {
        weight[index] = INF;
        rel.agregarRel(vAct, index);
        vAct = g.steVert(vAct);
    }
    prev[0]=
    weight[0] =0;
    for(int index=0; index < tamG; ++index)
    {
        pMen=INF;
        //Coger el vertice mas peque/o
        for(int indexP =0; indexP<tamG; ++indexP )
        {
            // Si se encuentra un peso mas peque/o, escoger este como el peso mas peque/o actual
            if(pMen > weight[indexP] && !d.pertenece(vTemp =rel.preImagen(indexP)))
            {
                vAct = vTemp;
                pMen= weight[indexP];
            }
        }
        // Agregar a que es usado y cual es el indice actual del vertice
        d.agregar(vAct);
        // Para todos los vertices adyacentes al actual
        for (vert hijoAct=g.primerVertAdy(vAct); hijoAct!=vertNulo ; hijoAct = g.steVertAdy(vAct, hijoAct))
        {
            //Si aun no se ha metido el vertice actual y existe una arista con peso menor
            if(!d.pertenece(hijoAct) && g.pesoArista(vAct,hijoAct) < weight[rel.imagen(hijoAct)])
            {
                // Que este sea el peso mas peque/o
                prev[rel.imagen(hijoAct)] = vAct;
                weight[rel.imagen(hijoAct)] = g.pesoArista(vAct,hijoAct);
            }
        }
    }
}
// Variables globales vendedor
int solucAct [MAXARRAY];
Dicc<vert> diccG;
int mejorSol[MAXARRAY];
int minCosto;
int cantidadSol;
int gananciaAct;
R1a1 <vert, int> relG;
int maxTamG;

void vendedor(Grafo &g)
{
    gananciaAct =0;
    minCosto =INF;
    cantidadSol =0;
    maxTamG = g.numVerts();
    vert vAct=g.primerVert();
    // Establecer relaciones
    for(int index =0; index< maxTamG;++index)
    {
        relG.agregarRel(vAct, index);
        vAct = g.steVert(vAct);
    }
    diccG.agregar(g.primerVert());
    vendedorR(g,1);
}

void limpiarVariablesGlobales()
{
    diccG.vaciar();
    relG.vaciar();
}

void imprimirVendedor(Grafo &g)
{
    // Imprimir solucion
    std::cout << "Hay " << cantidadSol << " soluciones factibles.\n";
    // Si no hay soluciones factibles, no imprime solucion optima
    if(cantidadSol !=0)
    {
        std::cout << "La solucion del problema del vendedor tiene una solucion optima de " << minCosto << " y la solucion siendo:\n";
        for(int index =0; index< maxTamG; ++index)
            std::cout <<g.etiqueta(relG.preImagen(mejorSol[index])) << " ";
        std::cout<< std::endl;
    }

}

void vendedorR(Grafo &g, int i)
{
    // Vaya desde el vertice actual hasta todos los adyacentes de este
    for(vert vAct = relG.preImagen(i), vAdy =g.primerVertAdy(vAct) ;vAdy!=vertNulo ;vAdy= g.steVertAdy(vAct, vAdy))
    {
        // Si se puede agregar
        if(!diccG.pertenece(vAdy))
        {
            diccG.agregar(vAdy);
            solucAct[i]= relG.imagen(vAdy);
            gananciaAct+= g.pesoArista(vAct, vAdy);
            // Si esta en el ultimo agregado
            if(i ==maxTamG-1 )
            {
                // Si se puede cerrar el ciclo se tienen una solucion factible
                if( g.adyacente(relG.preImagen(0), vAdy))
                {
                    ++cantidadSol;
                    gananciaAct+= g.pesoArista(relG.preImagen(0), vAdy);
                    // Si es mejor que la solucion anterior, haga esta la mejor solucion
                    if (gananciaAct < minCosto)
                    {
                        minCosto = gananciaAct;
                        for(int indexCopy =0; indexCopy < maxTamG; ++indexCopy)
                            mejorSol[indexCopy] = solucAct[indexCopy];
                    }
                }
            }
            else
            {
                // Llamada recursiva
                vendedorR(g, i+1);
            }
            // Arepentimiento
            gananciaAct -= g.pesoArista(vAct, vAdy);
            diccG.borrar(vAdy);
        }
    }
}

void imprimirDijkstra(Grafo &g,  vert v, vert *prev, int *dist, R1a1 <vert, int> &r)
{
    std:: cout << "Los caminos mas cortos para cada vertice es:\n";
    // Imprime los resultados
    int iAct;
    for(vert vAct =g.primerVert() ;vAct != vertNulo ;vAct = g.steVert(vAct))
    {
        iAct= r.imagen(vAct);

        if(dist[iAct] == INF)
            std:: cout << "No existe camino entre "<< g.etiqueta(v)  <<" y " << g.etiqueta(vAct) << "\n";
        else
        {
            std:: cout << "Camino de "<< g.etiqueta(v)  <<" a " << g.etiqueta(vAct) <<", con peso "<< dist[iAct] <<": "<< g.etiqueta(vAct)<< " ";
            // Hasta que se llegue al destino
            while(prev[iAct] !=vertNulo)
            {
                std:: cout << g.etiqueta((prev[iAct])) << " ";
                iAct = r.imagen(prev[iAct]);
            }
            std:: cout << std::endl ;
        }
    }
}

void imprimirPrim(Grafo &g, vert *prev, int *weight, R1a1 <vert, int>& rel)
{
    int tamG = g.numVerts();
    // Imprimir los resultados
    std::cout << "El arbol de minimo costo con Prim empezando en el vertice "<< g.etiqueta(rel.preImagen(0))<< " es:\n";
    for(int index=1; index < tamG; ++index)
    {
        std::cout << "La arista: (" << g.etiqueta(rel.preImagen(index)) << ", " << g.etiqueta(prev[index]) << ") con peso " <<  weight[index]<<std::endl;
    }
}

