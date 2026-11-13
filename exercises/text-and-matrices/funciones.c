/**//*                                                                    *//**/
/**//*                  DNI OMITIDO-PUCCI,FedericoAxel-(05-1965)           *//**/
/**//*                                                                    *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO DESDE ACÁ *//**/


/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO HASTA ACÁ *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* ACÁ DEBE DESARROLLAR LAS FUNCIONES Y PRIMITIVAS PEDIDAS    *//**//**/
/**//**//* ADEMÁS DE CUALQUIER OTRA FUNCIÓN QUE SE REQUIERA           *//**//**/




/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* FUNCIONES A DESARROLLAR                                            *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/***//***/
int esLetraODigito_MIO(char c)
{
    //YA SE QUE ESTA FUNCION NO ES OPTIMA, PERO ES MAS ENTENDIBLE AL PROGRAMADOR
    if(c>='A' && c<='Z')
        return 1;
    if(c>='a' && c<='z')
        return 1;
    if(c>='0' && c<='9')
        return 1;
    if(c=='á' || c=='Á')
        return 1;
    if(c=='é' || c=='É')
        return 1;
    if(c=='í' || c=='Í')
        return 1;
    if(c=='ó' || c=='Ó')
        return 1;
    if(c=='ú' || c=='Ú' || c=='ü' || c=='Ü')
        return 1;
    if(c=='ñ' || c=='Ñ')
        return 1;

    return 0;
}

char *proxPal_MIO(const char *s)
{
    //AVANZA HASTA QUE ENCUENTRA UN CARACTER VALIDO
    while(!esLetraODigito_MIO(*s)   && *s!='\n'    && *s!='\0')
    {
        s++;
    }
    return (char*)s;
}

char *finPal_MIO(const char *s)
{
    //AVANZA HASTA QUE ENCUENTRA UN CARACTER NO VALIDO
    while(esLetraODigito_MIO(*s))
        s++;
    return (char*)s;
}

size_t tamPal_MIO(const char *ini, const char *fin)
{
    //RETORNA LA RESTA DE LA POSICION FINAL DE LA CADENA MENOS LA POSICION INICIAL
    //ESO DA COMO RESULTADO SU TAMAÑO
    return fin-ini;
}

char *copiarPal_MIO(char *dest, const char *orig, size_t tam, int tope)
{
    //COPIA CARACTER A CARACTER LO QUE HAY EN ORIGEN EN DESTINO
    //TIENE EN CUENTA LOS TAMAÑOS Y EL TOPE
    char* c=dest;
    int cant=0;

    while(cant<tam && cant<tope)
    {
            *dest = *orig;
            dest++;
            orig++;
            cant++;
    }
    return c;
}
void guardarMatriz(char matrizPalabras[][TAM_PAL_MAX],
                   int cantPalabrasLargas,
                   int tamPalabraMasLarga,
                   FILE *fpPantalla)
{
    //ESTA FUNCION SIRVE PARA ESCRIBIR LA MATRIZ EN EL ARCHIVO
    int i;
    int j;
    for(i=0;i<cantPalabrasLargas;i++)
    {
        fprintf(fpPantalla," %2d - ",i+1);
        for(j=0;j<TAM_PAL_MAX;j++)
            fprintf(fpPantalla,"%c",*((*matrizPalabras+(i*TAM_PAL_MAX))+j));
        fprintf(fpPantalla, "\n");
    }
}


void procesarArchivo_MIO(FILE *fpEnt, FILE *fpPantalla)
{
    //ACA HAGO EL PROCESO PRINCIPAL
    if(fpEnt == NULL)
        return;
    int cantLineas=0;//CONTADOR DE LINEAS
    int cantLineasVacias=0;//CONTADOR DE LINEAS VACIAS
    int cantPalabras=0;//CONTADOR DE PALABRAS
    int tamPalabraActual=0;//TAMAÑO DE LA PALABRA RECIEN LEIDA
    int tamPalabraMasLarga=0;//TAMAÑO DE LA PALABRA MAS LARGA
    int cantPalabrasLargas=0;//CANTIDAD DE LAS PALABRAS CONTADAS CON EL TAMAÑO DE ARRIBA
    char linea[199];//VECTOR DE CHAR PARA LEER UNA LINEA DEL ARCHIVO
    char matrizPalabras[CANT_PAL_MAX][TAM_PAL_MAX];//MATRIZ QUE CONTIENE LAS PALABRAS CON EL MAXIMO TAMAÑO
    char* fP;//PUNTERO A FIN DE UNA PALABRA
    char* eP;//PUNTERO A INICIO DE UNA PALABRA
    while(fgets(linea,199,fpEnt))
    {
        eP=proxPal_MIO(linea);
        fP=finPal_MIO(eP);
        tamPalabraActual=tamPal_MIO(eP,fP);
        if(tamPalabraActual==0)
        {
            cantLineasVacias++;
        }
        else
        {
            while(*eP!='\n' && *eP!='\0') //ACA ENCONTRE UNA PALABRA
            {
                char palabra[25];
                copiarPal_MIO(palabra,eP,TAM_PAL_MAX,tamPalabraActual);
                cantPalabras++;
                if(tamPalabraActual>tamPalabraMasLarga)
                {
                    tamPalabraMasLarga=tamPalabraActual;
                    cantPalabrasLargas=0;
                }
                if(tamPalabraActual==tamPalabraMasLarga)
                {
                    if(cantPalabrasLargas<CANT_PAL_MAX)
                        copiarPal_MIO(matrizPalabras[cantPalabrasLargas],eP,TAM_PAL_MAX,tamPalabraActual);
                    cantPalabrasLargas++;
                }
                eP=proxPal_MIO(fP);
                fP=finPal_MIO(eP);
                tamPalabraActual=tamPal_MIO(eP,fP);
            }
        };
        cantLineas++;
    }
    if(cantLineas == 0)
    {
        fprintf(fpPantalla,"El archivo está vacío.\n");
    }
    else
    {
        fprintf(fpPantalla,"El archivo tiene un total de %d línea(s) de texto.\n",cantLineas);
        fprintf(fpPantalla,"Hay %d línea(s) sin palabras.\n",cantLineasVacias);
        fprintf(fpPantalla,"Hay un total de %d palabra(s).\n",cantPalabras);
        fprintf(fpPantalla,"La palabra más larga tiene %d caracter(es).\n",tamPalabraMasLarga);
        fprintf(fpPantalla,"Hay %d palabra(s) con esa cantidad de caracteres\n",cantPalabrasLargas);
        fprintf(fpPantalla,"Se muestra(n) la(s) %d palabra(s) más larga(s)\n",cantPalabrasLargas);
        guardarMatriz(matrizPalabras,cantPalabrasLargas,tamPalabraMasLarga,fpPantalla);
    }
}


int traspRespAlCentro_MIO(int mat[][M_COLUM], int filas, int colum)
{
    int i;
    int j;
    int aux;
    int centroDeMatriz;
    int cantElem;
    int finDeColumna=colum-1;
    int finDeFila=filas-1;
    int cont=0;//CANTIDAD DE ELEMENTOS MOSTRADOS
    cantElem=colum*filas;
    centroDeMatriz=cantElem/2;//ACA AVERIGUO EL CENTRO DE LA MATRIZ
                              //DESDE ESE ELEMENTO TENGO QUE TRASPONERLA
    for(i=0; i<filas && cont<centroDeMatriz; i++)
    {
        for(j=0; j<colum && cont<centroDeMatriz; j++)
        {
            aux=mat[finDeFila][finDeColumna];
            mat[finDeFila][finDeColumna]=mat[i][j];
            mat[i][j]=aux;
            finDeColumna--;
            cont++;
        }
        finDeColumna=colum-1;
        finDeFila--;
    }
    return cont;
}

int mostrarTriangSup_MIO(int mat[][M_COLUM], int filas, int colum,
                         FILE *fpPantalla)
{
    int i;
    int j;
    int cont=0;//CANTIDAD DE ELEMENTOS MOSTRADOS

    for(i=0; i<filas; i++)
    {
        for(j=i; j<colum; j++)//CON ESTA CONDICION SE MUESTRA LA TRIANGULAR SUPERIOR
                              //INCLUIDA LA DIAGONAL SECUNDARIA
        {
            fprintf(fpPantalla,"%4d",mat[i][j]);
            cont++;
        }
        fprintf(fpPantalla,"\n");
        fprintf(fpPantalla,"%*s", 4*(i+1)," ");
    }
    fprintf(fpPantalla,"\n");
    return cont;
}



