/**//*        EN LOS SIGUIENTES MACROREEMPLAZOS INDIQUE:                  *//**/
/**//*    APELLIDO(S)     (COMPLETO)                                      *//**/
/**//*    NOMBRE(S)       (COMPLETO)                                      *//**/
/**//*    NÚMERO DE DNI   (con los puntos de millón y de mil              *//**/
/**//*    COMISIÓN                                                        *//**/
#define APELLIDO    "PUCCI"
#define NOMBRE      "FEDERICO AXEL"
#define DOCUMENTO   "DNI OMITIDO"
#define COMISION    "05(1965)"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO DESDE ACÁ *//**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO HASTA ACÁ *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* ACÁ DEBE DESARROLLAR LAS FUNCIONES Y PRIMITIVAS PEDIDAS    *//**//**/
/**//**//* ADEMÁS DE CUALQUIER OTRA FUNCIÓN QUE SE REQUIERA           *//**//**/



int extraerNota(char*);
int buscarEnTablaFila2(const char letra,const char tabla[][COL_TABLA],
                       int fila);

/**       PUNTO 1 A **/

int comparar(const char*cad,const char *tab)
{
    int cant=0;
    while(*tab!='\0' && *cad!=*tab)     //comparo para ver si son iguales
    {
        //y si lo encuentra guardo la columna
        cant++;
        tab++;
    }
    return *tab=='\0'? -1:cant;
}
//le puse const a tab
char reemplazar(char*cad,const char*tab,int col)
{
    int i=0;
    while(i!=col)                   //me posiciono en la columna indicada y
    {
        //reemplazo
        tab++;
        i++;
    }

    *cad=*tab;
    return *cad;
}


int codificar_MIO(char *cadena, const char tabla[][COL_TABLA], int cantCol)
{
    char*cad = cadena;
    int col;
    int i=0;
    int cambios=0;

    if(*tabla[0]=='\0' || *tabla[1]=='\0') // pregunto si las tablas
        return 0;                          // de reemplazo y la cadena
    // no tiene nada
    while(*cad!='\0')
    {
        col=comparar(cad,tabla[i]);//comparo y si lo encuentra guardo colum
        if(col>=0)
        {
            *cad=reemplazar(cad,tabla[i+1],col);//reemplazo el caracter
        }
        cad++;
        cambios++;
    }
    return cambios;
}

int decodificar_MIO(char *cadena, const char tabla[][COL_TABLA], int cantCol)
{
    char*cad=cadena;
    int i=1;
    int col=0;
    int cambios=0;

    if(*tabla[0]=='\0' || *tabla[1]=='\0' ||*cad=='\0')
        return 0;

    while(*cad!='\0')
    {
        col=comparar(cad,tabla[i]);     //comparo el codificado con la 2da
        if(col>=0)                      // cadena de reemp
        {
            *cad=reemplazar(cad,tabla[i-1],col);    //al ser igual reemplazo
        }                                          //por la 1ra cadena
        cad++;
        cambios++;
    }
    return cambios;
}

/**       PUNTO 1 B **/

char bienFormada_MIO(const char tabla[][COL_TABLA], int colTabla)
{
    int i=0;

    while(i<colTabla)
    {
        if(buscarEnTablaFila2(tabla[0][i],tabla,2)==0)
            return tabla[0][i];
        else
            i++;
    }
    return '\0';
}

int buscarEnTablaFila2(const char letra,
                       const char tabla[][COL_TABLA],int fila)
{
    int i=0;
    while(letra!=tabla[1][i] && i<COL_TABLA)
        i++;
    if(i==COL_TABLA)
        return 0;
    else
        return 1;
}

/**                  FIN de PUNTO 1 **/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/** para crear y mostrar los datos de PUNTO 2 **/


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* FUNCIONES A DESARROLLAR                                            *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/** PARA PUNTO 2 **/
/** PUNTO 2 A **/

int actualizar_MIO(const char *archBin, const char *archTxt, FILE *fpPantalla)
{
    FILE* fpBin;
    FILE* fpTxt;
    fpBin=fopen(archBin,"r+b");
    fpTxt=fopen(archTxt,"rt");
    int valor = 0;

    if(!fpBin && !fpTxt)//NO SE PUDO ABRIR NINGUNO
    {
        fclose(fpBin);
        fpBin=fopen(archBin,"w+b");
        if(!fpBin)
        {
            fprintf(fpPantalla,
                    "ERROR - abriendo \"actual\".\n");
            fprintf(fpPantalla,
                "ERROR - abriendo \"noveda.txt\". ¿No hay actualizaciones?.\n"
                    );
            fclose(fpTxt);
            fclose(fpBin);
            return -3;
        }
    }

    if(!fpTxt)//NO SE PUDO ABRIR EL TXT
    {
        fprintf(fpPantalla,
            "ERROR - abriendo \"noveda.txt\". ¿No hay actualizaciones?.\n"
                );
        fclose(fpTxt);
        fclose(fpBin);
        return -2;
    }

    if(!fpBin)//NO SE PUDO ABRIR EL BINARIO CON MODO ESCRITURA / MODIFICACION
    {
        fclose(fpBin);
        fpBin=fopen(archBin,"w+b");
        valor++;
        if(!fpBin)//NO SE PUDO ABRIR EL BINARIO EN MODO ESCRITURA
        {
            fprintf(fpPantalla,"ERROR - abriendo \"actual\".\n");
            fclose(fpTxt);
            fclose(fpBin);
            return -1;
        }
    }

    if(feof(fpTxt) && feof(fpBin))//LOS DOS ESTAN VACIOS
    {
        fprintf(fpPantalla,"ERROR - abriendo \"actual\".\n");
        fprintf(fpPantalla,
                "ERROR - abriendo \"noveda.txt\". ¿No hay actualizaciones?.\n"
                );
        fclose(fpTxt);
        fclose(fpBin);
        return -3;
    }

    if(feof(fpTxt))//EL TXT ESTÁ VACIO
    {
        fprintf(fpPantalla,
                "ERROR - abriendo \"noveda.txt\". ¿No hay actualizaciones?.\n"
                );
        fclose(fpTxt);
        fclose(fpBin);
        return -2;
    }

    if(feof(fpBin))//EL BINARIO ESTÁ VACIO
    {
        fprintf(fpPantalla,"ERROR - abriendo \"actual\".\n");
        fclose(fpTxt);
        fclose(fpBin);
        return -1;
    }
    valor += leerTxtYActualizarBin_MIO(fpBin,fpTxt,fpPantalla);
    fclose(fpTxt);
    fclose(fpBin);
    return valor;
}

/** PUNTO 2 B **/

int leerTxtYActualizarBin_MIO(FILE *fpBin, FILE *fpTxt, FILE *fpPantalla)
{
    //LOS ARCHIVOS LLEGAN ABIERTOS, SIN ERRORES Y DESDE EL PRINCIPIO.
    tReg registro;
    char linea[120];
    int cantidadDeReemplazos = 0;
    int cantidadDeLecturas = 0;

    while(cantidadDeLecturas < 13 && fgets(linea,120,fpTxt))
    {
        if(trozarCampos_MIO(&registro,linea))
        {
            cantidadDeReemplazos+=buscarAlumno_MIO(fpBin,&registro);
        }
        else
        {
            fprintf(fpPantalla,"ERROR EN EL TROZADO DE CAMPOS");
            return -4;
        }
        cantidadDeLecturas++;
    }
    return cantidadDeReemplazos;
}

/** PUNTO 2 c **/

int trozarCampos_MIO(tReg *pReg, char *linea)
{
    char* pNombreYApellido = (*pReg).apynom;
    int posicionActual = 0;
    int finalizoCarga = 0;
    int blancosEliminados = 0;
    int caracteresAlmacenados = 0;
    char cadAuxiliar[TAM_NOTAS];

    while(*linea != '\n' && finalizoCarga == 0)
    {
        if(posicionActual == POS_DNI)
        {
            (*pReg).dni = atoi(linea);
        }

        if(posicionActual >= POS_APELLIDO && posicionActual <= POS_NOTAS)
        {
            while(isspace(*linea) && posicionActual < POS_NOTAS)
            {
                linea++;
                posicionActual++;
                blancosEliminados++;
            }
            if(posicionActual < POS_NOTAS)
            {
                if(posicionActual == POS_NOMBRE)
                {
                    *pNombreYApellido = ',';
                    pNombreYApellido++;
                    caracteresAlmacenados++;
                }
                if(blancosEliminados > 0 && caracteresAlmacenados < 27)
                {
                    *pNombreYApellido = ' ';
                    blancosEliminados = 0;
                    pNombreYApellido++;
                    caracteresAlmacenados++;
                }
                if(caracteresAlmacenados < 27)
                {
                    *pNombreYApellido = toupper(*linea);
                    pNombreYApellido++;
                    caracteresAlmacenados++;
                }
            }
            if(posicionActual == POS_NOTAS)
            {
                *pNombreYApellido = '\0';
            }
        }

        if(posicionActual == POS_NOTAS)
        {
            strncpy(cadAuxiliar, linea, TAM_NOTAS);
            (*pReg).p1 = extraerNota(cadAuxiliar);
        }

        if(posicionActual == POS_NOTAS + 2)
        {
            strncpy(cadAuxiliar, linea, TAM_NOTAS);
            (*pReg).r1 = extraerNota(cadAuxiliar);
        }


        if(posicionActual == POS_NOTAS + 6)
        {
            strncpy(cadAuxiliar, linea, TAM_NOTAS);
            (*pReg).p2 = extraerNota(cadAuxiliar);
        }


        if(posicionActual == POS_NOTAS + 8)
        {
            strncpy(cadAuxiliar, linea, TAM_NOTAS);
            (*pReg).r2 = extraerNota(cadAuxiliar);
        }

        if(posicionActual == POS_NOTAS + 12)
        {
            strncpy(cadAuxiliar, linea, TAM_NOTAS);
            (*pReg).prom = extraerNota(cadAuxiliar);
        }
        linea++;
        posicionActual++;
    }
    return 1;
}

int extraerNota(char* texto)
{
    if(toupper(*texto) == 'A' || toupper(*(texto + 1)) == 'A') return -1;
    if(toupper(*texto) == '-' || toupper(*(texto + 1)) == '-') return -1;
    return atoi(texto);
}

/** PUNTO 2 D **/

int buscarAlumno_MIO(FILE *fpBin, const tReg *registro)
{
    rewind(fpBin);
    tReg regLeido;
    fread(&regLeido,sizeof(tReg),1,fpBin);
    while(!feof(fpBin))
    {
        if(regLeido.dni==registro->dni)
        {
            fseek(fpBin,sizeof(tReg)*(-1),SEEK_CUR);
            fwrite(registro,sizeof(tReg),1,fpBin);
            fseek(fpBin,sizeof(tReg)*(0),SEEK_CUR);
            return 0;//ALUMNO ACTUALIZADO
        }
        fread(&regLeido,sizeof(tReg),1,fpBin);
    }
    fwrite(registro,sizeof(tReg),1,fpBin);//ALUMNO AGREGADO AL FINAL
    return 1;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

