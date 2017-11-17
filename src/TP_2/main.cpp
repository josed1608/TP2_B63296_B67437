#include <iostream>
#include <string>

//#include "grafoLista.h"
#include "grafoMatriz.h"
#include "colap.h"
#include "dicc.h"
#include "conjuntod.h"
#include "algoritmos.h"

void probarAlgoritmos(Grafo & grafo);

void probarOperadores(Grafo & grafo);

void grafoPredet(Grafo& grafo);

void verTiempos();

void impEtiquetas(Grafo& grafo);

void impAristas(Grafo& grafo);

int main()
{
    Grafo grafo = Grafo();
    grafoPredet(grafo);

	bool prueba = true;
	while(prueba){
		std::cout << "Bienvenido, para utilizar este programa de prueba, se le presentaran distintos menus con opciones indexadas por numeros y usted debera digitar el numero de "
					 "la opcion que desea y presionar enter para avanzar:\n"
					 "\t1. Probar algoritmos de grafos\n"
					 "\t2. Aplicar operadores basicos de grafos\n"
					 "\t3. Ver tiempos de ejecucion reales\n"
					 "\t4. Salir\n\n";
		int opcion = 0;
		std::cin >> opcion;
		switch(opcion)
		{
            case 1: probarAlgoritmos(grafo); break;
            case 2: probarOperadores(grafo); break;
			case 3: verTiempos(); break;
			default: prueba = false; break;
		}
    }
	return 0;
}

void probarOperadores(Grafo & grafo)
{
    bool prueba = true;
    std::string etiq, etiqSalida, etiqEntrada, nuevaEtiq;
    vert v;
    int peso = 0;
    while(prueba)
    {
        std::cout << "\t1.  Vaciar Grafo\n"
                     "\t2.  Grafo vacio?\n"
                     "\t3.  Agregar vertice\n"
                     "\t4.  Agregar arista (no debe existir)\n"
                     "\t5.  Modificar peso\n"
                     "\t6.  Eliminar vertice (solo vertices aislados)\n"
                     "\t7.  Eliminar arista (debe existir)\n"
                     "\t8.  Modificar etiqueta\n"
                     "\t9.  Numero de vertices\n"
                     "\t10. Numero de aristas de salida (vertices adyacentes)\n"
                     "\t11. Vertices adyacentes\n"
                     "\t12. Peso de una arista\n"
                     "\t13. Imprimir vertices del grafo\n"
                     "\t14. Imprimir aristas del grafo\n"
                     "\t15. Primer vertice\n"
                     "\t16. Siguiente vertice\n"
                     "\t17. Primer vertice adyacente\n"
                     "\t18. Siguiente vertice adyancente\n"
                     "\t19. Volver al menu principal\n";
		int opcion = 0;
		std::cin >> opcion;
		switch (opcion)
		{
		case 1:
			grafo.vaciar();
			break;
		case 2:
            (grafo.vacio() == true) ? std::cout <<  "vacio\n" : std::cout <<  "no vacio\n";
			break;
		case 3:
			std::cout << "Digite la etiqueta del vertice que desea agregar\n";
			std::cin >> etiq;
			grafo.agregarVert(etiq);
			break;
		case 4:
			std::cout << "Digite la etiqueta del vertice de salida\n";
			std::cin >> etiqSalida;
			std::cout << "Digite la etiqueta del vertice de entrada\n";
			std::cin >> etiqEntrada;
			std::cout << "Digite el peso de la arista\n";
			std::cin >> peso;
			grafo.agregarArista(buscarVertice(grafo, etiqSalida), buscarVertice(grafo, etiqEntrada), peso);
			break;
		case 5:
			std::cout << "Digite la etiqueta del vertice de salida\n";
			std::cin >> etiqSalida;
			std::cout << "Digite la etiqueta del vertice de entrada\n";
			std::cin >> etiqEntrada;
			std::cout << "Digite el nuevo peso de la arista\n";
			std::cin >> peso;
			grafo.modificarPeso(buscarVertice(grafo, etiqSalida), buscarVertice(grafo,etiqEntrada), peso);
			break;
		case 6:
			std::cout << "Digite la etiqueta del vertice que desea eliminar\n";
			std::cin >> etiq;
			grafo.eliminarVert(buscarVertice(grafo,etiq));
			break;
		case 7:
			std::cout << "Digite la etiqueta del vertice de salida\n";
			std::cin >> etiqSalida;
			std::cout << "Digite la etiqueta del vertice de entrada\n";
			std::cin >> etiqEntrada;
			grafo.eliminarArista(buscarVertice(grafo,etiqSalida), buscarVertice(grafo,etiqEntrada));
			break;
		case 8:
			std::cout << "Digite la etiqueta del vertice que desea modificar\n";
			std::cin >> etiq;
			std::cout << "Digite la nueva etiqueta\n";
			std::cin >> nuevaEtiq;
			grafo.modificarEtiq(buscarVertice(grafo,etiq), nuevaEtiq);
			break;
        case 9:
            std:: cout << grafo.numVerts() << std::endl;
			break;
        case 10:
			std::cout << "Digite la etiqueta del vertice al que desea conocer la cantidad de vertices adyacentes\n";
			std::cin >> etiq;
            std:: cout << grafo.numVertAdy(buscarVertice(grafo,etiq)) <<std::endl;
			break;
        case 11:
            std::cout << "Digite la etiqueta del vertice que de los vertices que se desea ver si son adyacentes\n";
            std::cin >> etiq;
            std::cout << "Digite la etiqueta del  otro vertice\n";
            std:: cin >> nuevaEtiq;
            (grafo.adyacente(buscarVertice(grafo,etiq), buscarVertice(grafo,nuevaEtiq)) == true )? std::cout << "Si\n" : std::cout << "No\n";
			break;
        case 12:
			std::cout << "Digite la etiqueta del vertice de salida\n";
			std::cin >> etiqSalida;
			std::cout << "Digite la etiqueta del vertice de entrada\n";
			std::cin >> etiqEntrada;
			std::cout << grafo.pesoArista(buscarVertice(grafo,etiqSalida), buscarVertice(grafo,etiqEntrada)) << std::endl;
			break;
        case 13:
			impEtiquetas(grafo);
			break;
        case 14:
			impAristas(grafo);
			break;
        case 15:
            if((v= grafo.primerVert())!= vertNulo)
                std::cout << "El primer vertice posee etiqueta: " << grafo.etiqueta(v) << std::endl;
			break;
        case 16:
			std::cout << "Digite la etiqueta del vertice que desea conocer su siguiente\n";
			std::cin >> etiq;
            if((v=grafo.steVert(buscarVertice(grafo, etiq))) != vertNulo)
                std::cout << "La etiquete del siguiente vertice es: " << grafo.etiqueta(v) << std::endl;
            else
                std::cout << "No tiene vertice siguiente"<< std::endl;
			break;
        case 17:
			std::cout << "Digite la etiqueta del vertice que desea conocer su primer adyacente\n";
			std::cin >> etiq;
            if((v=grafo.primerVertAdy(buscarVertice(grafo, etiq))) != vertNulo)
                std::cout << "La etiquete del primer vertice adyacente es: " << grafo.etiqueta(v) << std::endl;
            else
                std::cout <<"No tiene ningun vertice adyacente"<< std::endl;
			break;
        case 18:
            std::cout << "Digite la etiqueta del vertice origen de ver si tiene un siguiente vertice adyacente\n";
            std::cin >> etiq;
			std::cout << "Digite la etiqueta del vertice tras el cual desea otro adyacente\n";
			std::cin >> etiqEntrada;
            if ((v= grafo.steVertAdy(buscarVertice(grafo, etiq), buscarVertice(grafo, etiqEntrada)) ) != vertNulo)
                std::cout << "La etiquete del siguiente vertice es: " << grafo.etiqueta(v) << std::endl;
            else
                std::cout <<"No hay siguiente"<< std::endl;
			break;
		default:
			prueba = false;
			break;
		}
	}
}

void probarAlgoritmos(Grafo &grafo)
{
    bool prueba = true;
	int opcion, opcionFloyd;
	std::string etiq, etiqSalida, etiqEntrada;

	vert vectorVertices[grafo.numVerts()], vAct;
    int vectorEnteros[grafo.numVerts()];

	Grafo grafoCopiarIguales;
	grafoPredet(grafoCopiarIguales);

	int** pesos = new int*[grafo.numVerts()];
	vert** prevs = new vert*[grafo.numVerts()];
	for(int i=0; i < grafo.numVerts(); ++i)
	{
		pesos[i] = new int[grafo.numVerts()];
		prevs[i] = new vert[grafo.numVerts()];
	}

	bool pruebaFloyd = true;

    R1a1 <vert , int> rel ;
    while(prueba)
    {
        std::cout << "\t1.  Dijkstra\n"
                     "\t2.  Floyd\n"
                     "\t3.  Prim\n"
                     "\t4.  Kruskal\n"
                     "\t5.  Copiar grafo\n"
                     "\t6.  Iguales grafo\n"
                     "\t7.  Problema del vendedor\n"
                     "\t8.  Volver al menu principal\n";
        std::cin >> opcion;
        switch (opcion)
        {
        case 1:
            std::cout << "Digita la etiquta del vertice donde se va a calcular Dijkstra.\n";
            std::cin >> etiq;
            vAct = buscarVertice(grafo,etiq);
            dijkstra (grafo, vAct, vectorVertices, vectorEnteros, rel );
            imprimirDijkstra(grafo,vAct, vectorVertices, vectorEnteros, rel);
            rel.vaciar(); break;
		case 2:
			floyd(grafo, pesos, prevs, rel);
			while(pruebaFloyd)
			{
				std::cout << "Digite la etiqueta del vertice de salida\n";
				std::cin >> etiqSalida;
				std::cout << "Digite la etiqeta del vertice de llegada\n";
				std::cin >> etiqEntrada;
				imprimirCaminoFloyd(grafo, buscarVertice(grafo, etiqSalida), buscarVertice(grafo, etiqEntrada), pesos, prevs);
				std::cout << "Digite 1 para salir de la prueba de Floyd o 2 para preguntar por un nuevo camino\n";
				std::cin >> opcionFloyd;
				if(opcionFloyd == 1)
				{
					pruebaFloyd = false;
				}
			}
			rel.vaciar();
			break;
        case 3:
            prim(grafo, vectorVertices, vectorEnteros, rel );
            imprimirPrim(grafo,vectorVertices, vectorEnteros, rel);
            rel.vaciar(); break;
        case 4: kruskal(grafo); break;
		case 5:
			std::cout << "Se copio el grafo predeterminado en el grafo de pruebas\n";
			copiar(grafo, grafoCopiarIguales);
			break;
		case 6:
			std::cout << "Se compararan el grafo predeterminado con el actual grafo de pruebas\n";
			iguales(grafo, grafoCopiarIguales) == true ? std::cout << "iguales\n" : std::cout << "no son iguales\n";
			break;
        case 7:
            limpiarVariablesGlobales();
            vendedor(grafo);
            imprimirVendedor(grafo); break;
        default: prueba = false; break;
        }
    }

	for(int i=0; i < grafo.numVerts(); ++i)
	{
		delete[] pesos[i];
		delete[] prevs[i];
	}
	delete pesos;
	delete prevs;
}

void grafoPredet(Grafo& grafo)
{
    // Para cambiar matriz predeterminada es aqui
	grafo.agregarVert("A");
	grafo.agregarVert("B");
	grafo.agregarVert("C");
    grafo.agregarVert("D");
    grafo.agregarVert("E");
	//grafo.agregarVert("F");
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "B"), 3);
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "C"), 4);
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "D"), 2);
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "E"), 7);
    grafo.agregarArista(buscarVertice(grafo,"B"), buscarVertice(grafo, "C"), 4);
    grafo.agregarArista(buscarVertice(grafo,"B"), buscarVertice(grafo, "D"), 6);
    grafo.agregarArista(buscarVertice(grafo,"B"), buscarVertice(grafo, "E"), 3);
    grafo.agregarArista(buscarVertice(grafo,"C"), buscarVertice(grafo, "D"), 5);
    grafo.agregarArista(buscarVertice(grafo,"C"), buscarVertice(grafo, "E"), 8);
    grafo.agregarArista(buscarVertice(grafo,"D"), buscarVertice(grafo, "E"), 6);
    /*
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "C"), 7);
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "D"), 5);
    grafo.agregarArista(buscarVertice(grafo,"A"), buscarVertice(grafo, "E"), 2);
    grafo.agregarArista(buscarVertice(grafo,"B"), buscarVertice(grafo, "C"), 10);
    grafo.agregarArista(buscarVertice(grafo,"B"), buscarVertice(grafo, "E"), 8);
    grafo.agregarArista(buscarVertice(grafo,"C"), buscarVertice(grafo, "D"), 50);
    grafo.agregarArista(buscarVertice(grafo,"C"), buscarVertice(grafo, "E"), 6);
    grafo.agregarArista(buscarVertice(grafo,"D"), buscarVertice(grafo, "E"), 1);
    */
}

void verTiempos()
{

}

void impEtiquetas(Grafo& grafo)
{
	vert vertice = grafo.primerVert();
	while(vertice != vertNulo)
	{
		std::cout << grafo.etiqueta(vertice) << " | ";
		vertice = grafo.steVert(vertice);
	}
	std::cout << std::endl;
}

void impAristas(Grafo& grafo)
{
	Dicc<Arista> aristas = Dicc<Arista>();
	vert vertice = grafo.primerVert();
	while(vertice != vertNulo)
	{
		vert adyacente = grafo.primerVertAdy(vertice);
		while(adyacente != vertNulo)
		{
			if(!aristas.pertenece(Arista(vertice, adyacente, grafo.pesoArista(vertice, adyacente)))){
				std::cout << "(" << grafo.etiqueta(vertice) << ", " << grafo.etiqueta(adyacente) << ", " << grafo.pesoArista(vertice, adyacente) << ")\n";
				aristas.agregar(Arista(vertice, adyacente, grafo.pesoArista(vertice, adyacente)));
			}
			adyacente = grafo.steVertAdy(vertice, adyacente);
		}
		vertice = grafo.steVert(vertice);
	}
	std::cout << std::endl;
}

