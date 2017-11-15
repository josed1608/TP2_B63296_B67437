#include "algoritmos.h"
#define INF INT_MAX

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
                mat[i][j] = INF;
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

	imprimirMatrizFloyd(mat, grafo.numVerts(), grafo, rel);

	int n = grafo.numVerts();
	for(int k = 0; k < n; ++k)
	{
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				if(mat[i][k] != INF && mat[k][j] != INF)
				{
					if(mat[i][j] > mat[i][k] + mat[k][j])
						mat[i][j] = mat[i][k] + mat[k][j];
				}
			}
		}
	}

	imprimirMatrizFloyd(mat, grafo.numVerts(), grafo, rel);
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
    //if(g1.numVerts() != g2.numVerts() || g1.numAristas() != g2.numAristas()){
        //return false;
    //}

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

void dijkstra(Grafo &g, vert v)
{
    int tamG =g.numVerts(), pMen, cPes, iAct, dist [tamG];
    vert prev[tamG], vAct = g.primerVert(), vTemp, vMen;
    R1a1 <vert, int> r;
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

    std:: cout << "Los caminos mas cortos para cada vertice es:\n";
    // Imprime los resultados
    for(vAct =g.primerVert() ;vAct != vertNulo ;vAct = g.steVert(vAct))
    {
        iAct= r.imagen(vAct);
        if(dist[iAct] == INT_MAX)
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

void prim(Grafo &g)
{
    int tamG = g.numVerts(), weight[tamG], prev [tamG], pMen;
    R1a1 <vert , int> rel ;
    Dicc <vert> d;
    vert vAct =g.primerVert(), vTemp;
    for(int index=0; index < tamG; ++index)
    {
        weight[index] = INF;
        rel.agregarRel(vAct, index);
        vAct = g.steVert(vAct);
    }
    prev[0]=-1;
    weight[0] =0;
    for(int index=0, iAct; index < tamG; ++index)
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
        iAct = rel.imagen(vAct);
        // Para todos los vertices adyacentes al actual
        for (vert hijoAct=g.primerVertAdy(vAct); hijoAct!=vertNulo ; hijoAct = g.steVertAdy(vAct, hijoAct))
        {
            //Si aun no se ha metido el vertice actual y existe una arista con peso menor
            if(!d.pertenece(hijoAct) && g.pesoArista(vAct,hijoAct) < weight[rel.imagen(hijoAct)])
            {
                // Que este sea el peso mas peque/o
                prev[rel.imagen(hijoAct)] = iAct;
                weight[rel.imagen(hijoAct)] = g.pesoArista(vAct,hijoAct);
            }
        }
    }
    // Imprimir los resultados
    std::cout << "El arbol de minimo costo con Prim empezando en el vertice "<< g.etiqueta(rel.preImagen(0))<< " es:\n";
    for(int index=1; index < tamG; ++index)
    {
        std::cout << "La arista: (" << g.etiqueta(rel.preImagen(index)) << ", " << g.etiqueta(rel.preImagen(prev[index])) << ") con peso " <<  weight[index]<<std::endl;
    }
}

void vendedor(Grafo &g)
{

}
