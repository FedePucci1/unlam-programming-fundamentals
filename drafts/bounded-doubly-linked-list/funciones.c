/**//*             en los siguientes macroreemplazos indique:             *//**/
/**//*    su(s)         APELLIDO(S)     completo(s)                       *//**/
/**//*    su(s)         Nombre(S)       completo(s)                       *//**/
/**//*    su legajo     NÚMERO DE DNI   con los puntos de millón y de mil *//**/
/**//*    COMISIÓN                                                        *//**/
/**//*              reemplazando los que están como ejemplo               *//**/
#define APELLIDO    "PUCCI"
#define NOMBRE      "FEDERICO AXEL"
#define DOCUMENTO   "DNI OMITIDO"
#define COMISION    "05(1965)"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/** aquí insertaremos nuestras observaciones y / o correcciones              **/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#undef APELLIDO
#undef NOMBRE
#undef DOCUMENTO
#undef COMISION
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO DESDE ACÁ *//**/



/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO HASTA ACÁ *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"
#include "string.h"
#include "stdlib.h"


/** para el PUNTO 1 c.- **/
int compararNota(const void * d1, const void * d2)
{
    tEvalua * n1 = (tEvalua*)d1;
    tEvalua * n2 = (tEvalua*)d2;
    return n1->calif-n2->calif;
}

int compararClave(const void * d1, const void * d2)
{
    tEvalua * n1 = (tEvalua*)d1;
    tEvalua * n2 = (tEvalua*)d2;
    if(n1->calif == n2->calif)
        return strcmp(n2->clave,n1->clave);
    else
        return n1->calif-n2->calif;
}

int comparar(const void * d1, const void * d2)
{
    if(compararNota(d1, d2) == 0)
    {
        return compararClave(d1, d2);
    };
    return compararNota(d1, d2);
}

int ponerEnListaDoblNCalif_MIO(tListaDobl *lista, const void *nota,
                               size_t cantBytes, int tope)
{
    tNodoDobl *actual = *lista;
    tNodoDobl *auxiliarParaRecorrer = *lista;
    tNodoDobl *izq;
    tNodoDobl *der;
    tNodoDobl *nuevoNodo;
    tNodoDobl *desdeAcaElimino;
    tNodoDobl *posicionAInsertar;
    int notasDistintas = 1;
    int cantEliminados = 0;
    int compararConActual;
    int compararConDerecha;
    int casoDeAgregado;
    int flagElimine;

    // LISTA VACIA
    // PRIMER NODO
    if(!actual)
    {
        izq=der=NULL;
        nuevoNodo = (tNodoDobl*)malloc(sizeof(tNodoDobl));
        if(!nuevoNodo)
            return SIN_MEMORIA;
        nuevoNodo->info = malloc(cantBytes);
        if(!nuevoNodo->info)
        {
            free(nuevoNodo);
            return SIN_MEMORIA;
        }
        memcpy(nuevoNodo->info, nota, cantBytes);
        nuevoNodo->tamInfo = cantBytes;
        nuevoNodo->izq = izq;
        nuevoNodo->der = der;
    }
    else
    {
        while(auxiliarParaRecorrer->izq)
            auxiliarParaRecorrer= auxiliarParaRecorrer->izq;
        do
        {
            actual = auxiliarParaRecorrer;
            izq=actual->izq;
            der=actual->der;

            if(izq)
            {
                if(compararNota(actual->info, izq->info)!=0)
                {
                    desdeAcaElimino = actual;
                    if(compararNota(actual->info, nota)!=0)
                    {
                        notasDistintas++;
                    }
                }
            }
            else
            {
                if(compararNota(actual->info, nota)!=0)
                {
                    notasDistintas++;
                }
                desdeAcaElimino = actual;


            }

            compararConActual=comparar(nota, actual->info);
            if(!izq && compararConActual > 0)
            {
                posicionAInsertar = actual;
                casoDeAgregado = 1;
            }
            if(compararConActual < 0 && !der)
            {
                posicionAInsertar = actual;
                casoDeAgregado = 2;
            }
            if(compararConActual < 0 && der)
            {
                compararConDerecha = comparar(nota, der->info);
                if(compararConDerecha > 0)
                {
                    posicionAInsertar = actual;
                    casoDeAgregado = 3;
                }
            }
            auxiliarParaRecorrer = auxiliarParaRecorrer->der;
        }
        while(auxiliarParaRecorrer);



        if(notasDistintas <= tope || compararNota(nota, desdeAcaElimino->info) > 0)
        {
            flagElimine = 0;
            if(notasDistintas > tope && compararNota(nota, desdeAcaElimino->info) > 0)
            {
                tNodoDobl *auxIzq = desdeAcaElimino->izq;
                auxIzq->der = NULL;
                while(desdeAcaElimino)
                {
                    tNodoDobl *aux = desdeAcaElimino->der;
                    free(desdeAcaElimino->info);
                    free(desdeAcaElimino);
                    desdeAcaElimino = aux;
                    cantEliminados--;
                }
                flagElimine = 1;
            }

            nuevoNodo = (tNodoDobl*)malloc(sizeof(tNodoDobl));
            if(!nuevoNodo)
                return SIN_MEMORIA;
            nuevoNodo->info = malloc(cantBytes);
            if(!nuevoNodo->info)
            {
                free(nuevoNodo);
                return SIN_MEMORIA;
            }

            memcpy(nuevoNodo->info, nota, cantBytes);
            nuevoNodo->tamInfo = cantBytes;

            if(casoDeAgregado == 1)
            {
                nuevoNodo->izq = NULL;
                nuevoNodo->der = posicionAInsertar;
                posicionAInsertar->izq = nuevoNodo;
            }
            if(casoDeAgregado == 2)
            {
                nuevoNodo->izq = posicionAInsertar;
                nuevoNodo->der = NULL;
                posicionAInsertar->der = nuevoNodo;
            }
            if(casoDeAgregado == 3)
            {
                nuevoNodo->izq = posicionAInsertar;
                nuevoNodo->der = posicionAInsertar->der;
                posicionAInsertar->der->izq = nuevoNodo;
                posicionAInsertar->der = nuevoNodo;
            }
        }
        else
        {
            return NO_SE_INSERTA;
        }
    }
    *lista = nuevoNodo;
    return flagElimine == 0 ? TODO_BIEN : cantEliminados;
}

/**                  FIN de PUNTO 1 **/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

