#include <iostream>
#include <string>

//#include "grafoLista.h"
#include "grafoMatriz.h"
#include "colap.h"
#include "dicc.h"
#include "conjuntod.h"
#include "arista.h"

void probarAlgoritmos();

void probarOperadores();

void verTiempos();

vert buscarVertice(Grafo &grafo, std::string etiq);

void impEtiquetas(Grafo& grafo);

void impAristas(Grafo& grafo);

int main()
{
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
			case 1: probarAlgoritmos(); break;
			case 2: probarOperadores(); break;
			case 3: verTiempos(); break;
			default: prueba = false; break;
		}
    }
	return 0;
}

void probarOperadores()
{
    bool prueba = true;
    Grafo grafo = Grafo();
    std::string etiq, etiqSalida, etiqEntrada, nuevaEtiq;
    vert v;
    int peso = 0;
    grafo.agregarVert("a");
    grafo.agregarVert("b");
    grafo.agregarVert("c");
    grafo.agregarVert("d");
    grafo.agregarArista(1 , 4, 2);
    grafo.agregarArista(1 , 3, 3);
    grafo.agregarArista(4 , 3, 5);


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

void probarAlgoritmos()
{

}

void verTiempos()
{

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

