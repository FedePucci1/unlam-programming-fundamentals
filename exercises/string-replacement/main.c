#include "Ejercicio2p1.h"

int main()
{
    char c1[]={"Messi Aguero Di Maria Martinez Acunia Martinez"};
    char c2[]={"Martinez"};
    char c3[]={"Lautaro"};
    printf("\tCADENA SIN REEMPLAZOS:\n%s",c1);
    buscarYReemplazar(c1,miStrlen(c1),c2, c3);
    printf("\n\tCADENA CON REEMPLAZOS, REEMPLAZO %s POR %s:\n%s",c2,c3,c1);
    return 0;
}
