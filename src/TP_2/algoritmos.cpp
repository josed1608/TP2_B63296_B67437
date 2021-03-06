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

void floyd(Grafo& grafo, int **pesos, vert **prevs, R1a1<vert, int> &rel)
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

void imprimirCaminoFloyd(Grafo &grafo, vert vInicio, vert vFinal, int **pesos, vert **prevs, R1a1<vert, int> &rel)
{
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
    weight[0]= 0;
    prev[0]= vertNulo;
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
vert solucAct [MAXARRAY];
Dicc<vert> diccG;
vert mejorSol[MAXARRAY];
int minCosto;
int cantidadSol;
int gananciaAct;
int maxTamG;

void vendedor(Grafo &g)
{
	diccG.vaciar();
    gananciaAct =0;
    minCosto =INF;
    cantidadSol =0;
    maxTamG = g.numVerts();
    vert vPrimero = g.primerVert();
    solucAct[1]= mejorSol[1]= vPrimero ;
    diccG.agregar(vPrimero);
    vendedorR(g, 2);
}

void limpiarVariablesGlobales()
{
    diccG.vaciar();
}

void imprimirVendedor(Grafo &g)
{
    // Imprimir solucion
    std::cout << "Hay " << cantidadSol << " soluciones factibles.\n";
    // Si no hay soluciones factibles, no imprime solucion optima
    if(cantidadSol !=0)
    {
        std::cout << "La solucion del problema del vendedor tiene una solucion optima de " << minCosto << " y la solucion siendo:\n";
        for(int index =1; index<= maxTamG; ++index)
            std::cout <<g.etiqueta(mejorSol[index]) << " ";
        std::cout<< std::endl;
    }

}

void vendedorR(Grafo &g, int i)
{
    // Vaya desde el vertice actual hasta todos los adyacentes de este
    for(vert vAdy= g.primerVertAdy(solucAct[i-1]); vAdy!= vertNulo ; vAdy= g.steVertAdy(solucAct[i-1], vAdy))
    {
        // Si se puede agregar
        if( !diccG.pertenece(vAdy))
        {
            diccG.agregar(vAdy);
            solucAct[i]= vAdy;
            gananciaAct+= g.pesoArista(solucAct[i-1], vAdy);
            // Si esta en el ultimo agregado
            if(i == maxTamG)
            {
                // Si se puede cerrar el ciclo si se tiene una solucion factible
                if( g.adyacente(g.primerVert(), vAdy))
                {
                    ++cantidadSol;
                    // Agregar el peso entre el ultimo y el actual
                    gananciaAct+= g.pesoArista(g.primerVert(), vAdy);
                    // Si es mejor que la solucion anterior, haga esta la mejor solucion
                    if (gananciaAct < minCosto)
                    {
                        minCosto = gananciaAct;
                        for(int indexCopy =2; indexCopy <= maxTamG; ++indexCopy)
                            mejorSol[indexCopy] = solucAct[indexCopy];
                    }
                    // Arrepentimiento de el ultimo
                    gananciaAct-= g.pesoArista(g.primerVert(), vAdy);
                }
            }
            else
            {
                // Llamada recursiva
                vendedorR(g, i+1);
            }

            // Arepentimiento
            gananciaAct -= g.pesoArista(solucAct[i-1], vAdy);
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
	for(int index=1; index < tamG; ++index)
    {
        std::cout << "La arista: (" << g.etiqueta(rel.preImagen(index)) << ", " << g.etiqueta(prev[index]) << ") con peso " <<  weight[index]<<std::endl;
    }
}


void grafoCompleto(Grafo &g, int tam)
{
    // Crea las aristas aisladas
    grafoAislado(g,tam);
    // Une todas las aristas
    int times=g.numVerts()-1, index=1;
    for(vert vPrin =g.primerVert(), vAct; index<=times; vPrin= g.steVert(vPrin), ++index)
    {
        vAct= g.steVert(vPrin);
        for(; vAct!= vertNulo; vAct=g.steVert(vAct))
        {
            g.agregarArista(vPrin, vAct, rand()% 100+1);
        }
    }
}

void grafoTodosAUno(Grafo& g, int tam)
{
	grafoAislado(g, tam);
	vert principal = g.primerVert();
	for(vert ady = g.steVert(principal); ady != vertNulo; ady = g.steVert(ady))
	{
		g.agregarArista(principal, ady, rand()%100+1);
	}
}

void grafoAleatorio(Grafo& g, int verts, int aristas)
{
	Dicc<Arista> agregadas;
	R1a1<vert, int> rel;
	// Crea los vertices
	for(int index=1; index<=verts; ++index)
	{
		rel.agregarRel(g.agregarVert(std::to_string(index)), index);
	}

	//Primero me debo asegurar que sea conexo, para Prim y Kruskal
	for(vert act = g.primerVert(); g.steVert(act) != vertNulo; act = g.steVert(act))
	{
		vert ste = g.steVert(act);
		agregadas.agregar( Arista(act, ste));
		g.agregarArista(act, ste, rand()%100+1);
	}
	aristas -=(verts-1);

	//Agrego aristas hasta que ya no tenga que agregar mas
	while(aristas != 0)
	{
		vert v1 = rel.preImagen(rand()%verts + 1);
		vert v2 = rel.preImagen(rand()%verts + 1);
		if(v1 != v2 && !agregadas.pertenece(Arista(v1, v2)))
		{
			agregadas.agregar( Arista(v1, v2));
			g.agregarArista(v1, v2, rand()%100+1);
			--aristas;
		}
	}

}

void grafoAislado(Grafo &g, int tam)
{
    // Crea los vertices
    for(int index=1; index<=tam; ++index)
    {
        g.agregarVert(std::to_string(index));
    }

}

std::chrono::duration<double> calcPromDij(Grafo & g, vert * prev, int * dist, R1a1 <vert, int> r)
{
    std::chrono::duration<double> total;

    for(vert vAct = g.primerVert(); vAct!=vertNulo; vAct= g.steVert(vAct))
    {
        auto inicio = std::chrono::high_resolution_clock::now();
        dijkstra(g, g.primerVert(), prev, dist, r);
        auto fin = std::chrono::high_resolution_clock::now();
        total += fin-inicio;
        r.vaciar();
    }
    std::chrono::duration<double> promedio = total/((double)g.numVerts());
    return promedio;
}

void tiempoDijkstra(std::ofstream& archivo)
{
    std::chrono::duration<double> total;
	archivo << "Dijkstra\n"
			   "Grafos pequenos:\n";

    vert prev [GRA];
    int dist[GRA];
    R1a1 <vert, int> r;

	total = calcPromDij(todAUnoPeq,prev,dist,r);
	archivo << "\tEl promedio de grafo todos a uno es: " << total.count() << std::endl;

	total = calcPromDij(aleatorioPeq,prev,dist,r);
	archivo << "\tEl promedio de grafo aleatorio es: " << total.count() << std::endl;

	total = calcPromDij(aisladoPeq,prev, dist, r);
    archivo << "\tEl promedio de grafo aislado: " << total.count() << std::endl;

	total = calcPromDij(completoPeq,prev, dist, r);
    archivo << "\tEl promedio de grafo completo: " << total.count() << std::endl;

    //medianos
    archivo << "Grafos medianos:\n";

	total = calcPromDij(todAUnoMed,prev,dist,r);
	archivo << "\tEl promedio de grafo todos a uno es: " << total.count() << std::endl;

	total = calcPromDij(aleatorioMed,prev,dist,r);
	archivo << "\tEl promedio de grafo aleatorio es: " << total.count() << std::endl;

	total = calcPromDij(aisladoMed,prev, dist, r);
    archivo << "\tEl promedio de grafo aislado: " << total.count() << std::endl;

	total = calcPromDij(completoMed,prev, dist, r);
    archivo << "\tEl promedio de grafo completo: " << total.count() << std::endl;

    //grandes
    archivo << "Grafos grandes:\n";

	total = calcPromDij(todAUnoGra,prev,dist,r);
	archivo << "\tEl promedio de grafo todos a uno es: " << total.count() << std::endl;

	total = calcPromDij(aleatorioGra,prev,dist,r);
	archivo << "\tEl promedio de grafo aleatorio es: " << total.count() << std::endl;

	total = calcPromDij(aisladoGra,prev, dist, r);
    archivo << "\tEl promedio de grafo aislado: " << total.count() << std::endl;

	total = calcPromDij(completoGra,prev, dist, r);
    archivo << "\tEl promedio de grafo completo: " << total.count() << std::endl;
}

void tiemposFloyd(std::ofstream &archivo)
{
	std::chrono::duration<double> total;
	archivo << "Floyd\n"
			   "Grafos pequenos:\n";

	int** pesos = new int*[GRA];
	vert** prevs = new vert*[GRA];
	for(int i=0; i < GRA; ++i)
	{
		pesos[i] = new int[GRA];
		prevs[i] = new vert[GRA];
	}

	R1a1 <vert, int> r;

	auto inicio = std::chrono::high_resolution_clock::now();
	floyd(todAUnoPeq, pesos, prevs, r);
	auto fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(aleatorioPeq, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(aisladoPeq, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aislado: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(completoPeq, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

	//medianos
	archivo << "Grafos medianos:\n";

	inicio = std::chrono::high_resolution_clock::now();
	floyd(todAUnoMed, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(aleatorioMed, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(aisladoMed, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aislado: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(completoMed, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

	//grandes
	archivo << "Grafos grandes:\n";

	inicio = std::chrono::high_resolution_clock::now();
	floyd(todAUnoGra, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(aleatorioGra, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(aisladoGra, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aislado: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	floyd(completoGra, pesos, prevs, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

	for(int i=0; i < GRA; ++i)
	{
		delete[] pesos[i];
		delete[] prevs[i];
	}
	delete pesos;
	delete prevs;
}

void tiemposPrim(std::ofstream& archivo)
{
    std::chrono::duration<double> total;
	archivo << "Prim:\n"
			   "Grafos pequenos:\n";

    vert prev [GRA];
    int dist[GRA];
    R1a1 <vert, int> r;

	auto inicio = std::chrono::high_resolution_clock::now();
	prim(todAUnoPeq, prev, dist, r);
	auto fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	prim(aleatorioPeq, prev, dist, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

    inicio = std::chrono::high_resolution_clock::now();
	prim(completoPeq, prev, dist, r);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    r.vaciar();
    archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

    //medianos
    archivo << "Grafos medianos:\n";

	inicio = std::chrono::high_resolution_clock::now();
	prim(todAUnoMed, prev, dist, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	prim(aleatorioMed, prev, dist, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

    inicio = std::chrono::high_resolution_clock::now();
	prim(completoMed, prev, dist, r);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    r.vaciar();
    archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

    //grandes
    archivo << "Grafos grandes:\n";

	inicio = std::chrono::high_resolution_clock::now();
	prim(todAUnoGra, prev, dist, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	prim(aleatorioGra, prev, dist, r);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

    inicio = std::chrono::high_resolution_clock::now();
	prim(completoGra, prev, dist, r);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    r.vaciar();
    archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;
}

void tiemposKruskal(std::ofstream &archivo)
{
	std::chrono::duration<double> total;
	archivo << "Kruskal:\n"
			   "Grafos pequenos:\n";

	R1a1 <vert, int> r;
    //Peque/os
	auto inicio = std::chrono::high_resolution_clock::now();
	kruskal(todAUnoPeq);
	auto fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(aleatorioPeq);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(completoPeq);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

	//medianos
	archivo << "Grafos medianos:\n";

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(todAUnoMed);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(aleatorioMed);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(completoMed);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;

	//grandes
	archivo << "Grafos grandes:\n";

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(todAUnoGra);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo todos a uno es: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(aleatorioGra);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo aleatorio: " << total.count() << std::endl;

	inicio = std::chrono::high_resolution_clock::now();
	kruskal(completoGra);
	fin = std::chrono::high_resolution_clock::now();
	total = fin-inicio;
	r.vaciar();
	archivo << "\tEl tiempo de grafo completo: " << total.count() << std::endl;
}

void tiemposVendedor(std::ofstream& archivo)
{
    std::chrono::duration<double> total;
	archivo << "Vendedor\n"
			   "Grafos pequenos:\n";

    Grafo g = Grafo();
    grafoAislado(g, PEQV);
    auto inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    auto fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo aislado es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoCompleto(g, PEQV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo completo es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoTodosAUno(g, PEQV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo todo a uno es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoAleatorio(g, PEQV, PEQV_ARI);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo aleatorio es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    //medianos
    archivo << "Grafos medianos:\n";

    grafoAislado(g, MEDV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo aislado es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoCompleto(g, MEDV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo completo es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoTodosAUno(g, MEDV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo todo a uno es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoAleatorio(g, MEDV, MEDV_ARI);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo aleatorio es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    //grandes
    archivo << "Grafos grandes:\n";

    grafoAislado(g, GRAV);
     inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo aislado es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoCompleto(g, GRAV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo completo es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoTodosAUno(g, GRAV);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    g.vaciar();
    archivo << "\tEl tiempo de grafo todo a uno es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;

    grafoAleatorio(g, GRAV, GRAV_ARI);
    inicio = std::chrono::high_resolution_clock::now();
    vendedor(g);
    fin = std::chrono::high_resolution_clock::now();
    total = fin-inicio;
    archivo << "\tEl tiempo de grafo aleatorio es: " << total.count() << std::endl;
    archivo << "\tSoluciones factibles: " << cantidadSol << std::endl;
	if(minCosto!=INF)
        archivo << "\tSolucion optima: " <<  minCosto <<std::endl;
    else
        archivo << "No hay solucion." <<std::endl;
}

Grafo aisladoPeq;
Grafo aisladoMed;
Grafo aisladoGra;

Grafo completoPeq;
Grafo completoMed;
Grafo completoGra;

Grafo todAUnoPeq;
Grafo todAUnoMed;
Grafo todAUnoGra;

Grafo aleatorioPeq;
Grafo aleatorioMed;
Grafo aleatorioGra;

void crearGrafosTiempos()
{
	grafoAislado(aisladoPeq, PEQ);
	grafoAislado(aisladoMed, MED);
	grafoAislado(aisladoGra, GRA);

	grafoCompleto(completoPeq, PEQ);
	grafoCompleto(completoMed, MED);
	grafoCompleto(completoGra, GRA);

	grafoTodosAUno(todAUnoPeq, PEQ);
	grafoTodosAUno(todAUnoMed, MED);
	grafoTodosAUno(todAUnoGra, GRA);

	grafoAleatorio(aleatorioPeq, PEQ, PEQ_ARI);
	grafoAleatorio(aleatorioMed, MED, MED_ARI);
	grafoAleatorio(aleatorioGra, GRA, GRA_ARI);
}

void limpiarGrafosTiempos()
{
	aisladoPeq.vaciar();
	aisladoMed.vaciar();
	aisladoGra.vaciar();
	completoPeq.vaciar();
	completoMed.vaciar();
	completoGra.vaciar();
	todAUnoGra.vaciar();
	todAUnoMed.vaciar();
	todAUnoPeq.vaciar();
	aleatorioGra.vaciar();
	aleatorioMed.vaciar();
	aleatorioPeq.vaciar();
}
