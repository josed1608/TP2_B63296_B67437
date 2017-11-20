#ifndef COLAP_H
#define COLAP_H

#define MAXH 300*300

template <typename DataType>
class ColaP
{

    struct Par
    {
        DataType etiqueta;
        int prioridad;
        Par(DataType etiqueta= DataType(), int prioridad=0):
            etiqueta{etiqueta}, prioridad{prioridad}
        {
        }
    };

    Par vectHeap [MAXH+1];
    int n;


public:
	ColaP()
        :n{0}
    {
    }

    inline void vaciar(){n =0;}

    inline bool vacia(){return (n==0)? true :false;}

    inline int numElem(){return n;}

    void agregar(DataType e, int p)
    {
        ++n;
        vectHeap[n] = Par(e,p);
        Par swap;
        //Reorganizacion
        for (int i= n ; vectHeap[i/2].prioridad> vectHeap[i].prioridad && i !=1; i/=2)
        {
            swap = vectHeap[i/2];
            vectHeap[i/2] = vectHeap[i];
            vectHeap[i] = swap;
        }
    }

    DataType sacar()
    {
        //Sacado logico
        Par value = vectHeap[1];
        //Sacado fisico
        vectHeap[1] = vectHeap[n];
        bool seguir = true;
        Par swap;
        --n;
        for(int i=1, childInd; i+i<=n && seguir;)
        {
            childInd = i+i;
            // Tiene hijo derecho y si este es mas pequeno que el otro hijo
            if(i+i+1<=n && vectHeap[i+i+1].prioridad< vectHeap[i+i].prioridad)
                childInd +=1;
            // Si el mas pequeno es mayor, se detiene el recorrido
            if(vectHeap[i].prioridad < vectHeap[childInd].prioridad)
                seguir= false;
            // Intercambia valores
            else
            {
                swap = vectHeap[childInd];
                vectHeap[childInd] = vectHeap[i];
                vectHeap[i] = swap;
                i = childInd;
            }
        }

        return value.etiqueta;
    }

   inline ~ColaP(){n =0;}
};

#endif // COLAP_H
