#include "Ejercicio1.h"

void crearLista(tLista* l)
{
    *l=NULL;
}

int	ponerEnOrden(tLista *p,void *d, unsigned cantBytes,
                 int (*comparar)(void *,void *))
{
    tNodo	*nue;
    while(*p && comparar((*p)->info, d) < 0)
        p = &(*p)->sig;
    if((nue = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
       (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return -3;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;
    return 1;
}

int sacarPrimeroLista(tLista *l, void *d, unsigned cantBytes)
{
    tNodo *aux = *l;
    if(aux == NULL)
        return 0;
    *l = aux->sig;
    memcpy(d, aux->info, MINIMO(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int listaVacia(const tLista *l)
{
    return *l==NULL;
}

void crearArchivos(char* narch1,char* narch2)
{
    tMovimiento m[]={
                        {"20200101010101","1111111",'C',"100000.00"},
                        {"20200101010101","1111111",'C',"1.52"},
                        {"20200201010101","2222222",'C',"200000.00"},
                        {"20200301010101","3333333",'D',"200000.00"},
                        {"20200401010101","2222222",'D',"200000.00"},
                        {"20200401010101","2222222",'D',"200000.00"},
                        {"20200401010101","2222222",'D',"200000.00"},
                        {"20200401010101","2222222",'D',"200000.00"},
                        {"20200401010101","2222222",'D',"200000.00"},
                    };
    tCuenta c[]={
                    {"1111111/1",1111,"Messi",1000},
                    {"2222222/1",2222,"Aguero",1000},
                    {"3333333/1",3333,"Lautaro",1000},
                    {"4444444/1",4444,"Acunia",1000}
                };
    int i;
    FILE* fp1=fopen(narch1,"wb");
    FILE* fp2=fopen(narch2,"wt");

    fwrite(c,sizeof(c),1,fp1);
    for(i=0;i<9;i++)
    {
        fprintf(fp2,"%14s%7s%c%s\n",m[i].fecha,m[i].cuenta,m[i].movimiento,m[i].importe);
    }

    fclose(fp1);
    fclose(fp2);
}

void mostrarArchivoCuentas(char* narch1)
{
    FILE* fp1=fopen(narch1,"rb");
    tCuenta c;

    fread(&c,sizeof(tCuenta),1,fp1);
    while(!feof(fp1))
    {
        printf("%s\t%ld\t%s\t%.2lf\n",c.cuenta,c.dni,c.apyn,c.saldo);
        fread(&c,sizeof(tCuenta),1,fp1);
    }
    fclose(fp1);
}

void mostrarArchivoMovimientos(char* narch2)
{
    FILE* fp=fopen(narch2,"rt");
    char linea[50];
    tMovimiento d;

    while(fgets(linea,50,fp))
    {
        parsearLF(linea,&d);
        printf("%s %s %c %s\n",d.fecha,d.cuenta,d.movimiento,d.importe);
    }
    fclose(fp);
}

void parsearLF(char* buff,tMovimiento* d)
{

    char* aux=buff+31;
    *aux='\0';

    aux-=9;
    strcpy(d->importe,aux);
    *aux='\0';

    aux-=1;
    sscanf(aux,"%c",&d->movimiento);
    *aux='\0';

    aux-=7;
    strcpy(d->cuenta,aux);
    *aux='\0';

    strcpy(d->fecha,buff);
    *aux='\0';
}

void ponerEnListaOrdenadaArchivoMovimientos(tLista* l,char *narch2)
{
    FILE* fp=fopen(narch2,"rt");
    char linea[50];
    tMovimiento d;

    while(fgets(linea,50,fp))
    {
        parsearLF(linea,&d);
        ponerEnOrden(l,&d,sizeof(tMovimiento),compararMovs);
    }
    fclose(fp);
}

int actualizarArchivoCuentas(char* narch1,tLista* l)
{
    FILE* fp=fopen(narch1,"rb+");
    tMovimiento d;
    tCuenta c;

    while(!listaVacia(l))
    {
        sacarPrimeroLista(l,&d,sizeof(tMovimiento));
        rewind(fp);
        fread(&c,sizeof(tCuenta),1,fp);
        while(!feof(fp))
        {
            if(strncmp(c.cuenta,d.cuenta,7)==0)
            /*LA FUNCION STRNCMP A VECES FALLA SEGUN EL COMPILADOR
            MIS PROFESORES ANTERIORES TENIAN PROBLEMAS PARA LEERLA
            LO QUE HACE ES COMPARAR LAS DOS CADENAS HASTA EL NUMERO N
            QUE EN ESTE CASO ES EL 7*/
            {
                fseek(fp,-1L*sizeof(tCuenta),SEEK_CUR);
                if(d.movimiento=='C')
                    c.saldo+=atof(d.importe);
                else
                    c.saldo-=atof(d.importe);
                fwrite(&c,sizeof(tCuenta),1,fp);
                fseek(fp,0L,SEEK_CUR);
            }
            fread(&c,sizeof(tCuenta),1,fp);
        }
    }
    fclose(fp);
    return 1;
}

int compararMovs(void* d1,void* d2)
{
    tMovimiento* f1=(tMovimiento*)d1;
    tMovimiento* f2=(tMovimiento*)d2;
    return strcmp(f1->fecha,f2->fecha);
}

