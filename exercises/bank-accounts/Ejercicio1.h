#ifndef EJERCICIO1_H_INCLUDED
#define EJERCICIO1_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MINIMO(x,y) (x<=y)? x:y

typedef struct
{
    char cuenta[11];
    long dni;
    char apyn[41];
    double saldo;
}tCuenta;

typedef struct
{
    char fecha[15];
    char cuenta[9];
    char movimiento;
    char importe[10];
}tMovimiento;

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista* l);
int	ponerEnOrden(tLista *p,void *d, unsigned cantBytes,
                 int (*comparar)(void *,void *));
int sacarPrimeroLista(tLista *l, void *d, unsigned cantBytes);
int listaVacia(const tLista *l);

int compararMovs(void* d1,void* d2);
int acumularMovs(void* d1,void* d2);

void parsearLF(char* buff,tMovimiento* d);

void crearArchivos(char* narch1,char* narch2);
void mostrarArchivoCuentas(char* narch1);
void mostrarArchivoMovimientos(char* narch2);

void ponerEnListaOrdenadaArchivoMovimientos(tLista* l,char *narch2);

int actualizarArchivoCuentas(char* narch1,tLista* l);

#endif // EJERCICIO1_H_INCLUDED
