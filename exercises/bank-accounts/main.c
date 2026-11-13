#include "Ejercicio1.h"

int main()
{
    char narch1[]={"cuentas.dat"};
    char narch2[]={"movimientos.txt"};
    tLista l;

    crearLista(&l);

    crearArchivos(narch1,narch2);
    printf("\tARCHIVO CUENTAS SIN ACTUALIZAR:\n");
    mostrarArchivoCuentas(narch1);
    printf("\n\tARCHIVO DE MOVIMIENTOS:\n");
    mostrarArchivoMovimientos(narch2);

    ponerEnListaOrdenadaArchivoMovimientos(&l,narch2);

    actualizarArchivoCuentas(narch1,&l);

    printf("\n\tARCHIVO CUENTAS ACTUALIZADO:\n");
    mostrarArchivoCuentas(narch1);
    return 0;
}
