#include "Ejercicio2p1.h"

int buscarYReemplazar(char *cade, int tam,const char *busc, const char *reem)
{
    char* inireem=(char*)reem;
    char* inibusc=(char*)busc;
    char* inicade=(char*)cade;
    char* fincade=(char*)cade;
    char* fincadecopiar;
    int masomenos;
    char* fincadepegar;
    int cantpalbusc=0, cantpalreemp=0, cantpalcade=0, cantveces=0;

    while(*fincade!='\0')
        fincade++;

    while(*busc!='\0')
    {
        busc++;
        cantpalbusc++;
    }
    busc=inibusc;

    while(*reem!='\0')
    {
        reem++;
        cantpalreemp++;
    }
    reem=inireem;

    while(*cade!='\0')
    {
        cade++;
        cantpalcade++;
    }
    cade=inicade;
    int diferencia=cantpalreemp-cantpalbusc;

    while(*cade!='\0')
    {
        while(tolower(*cade)==tolower(*busc) && *busc!='\0')
        {
            busc++;
            cade++;
        }
        if(*busc=='\0' && cantpalcade+diferencia<=tam)
        {
            cantveces++;
            cantpalcade+=diferencia;
            if(diferencia>0)
            {
                fincadecopiar=fincade;
                fincade+=diferencia;
                fincadepegar=fincade;
                masomenos=-1;
            }
            else
            {
                fincadecopiar=cade;
                fincadepegar=cade+diferencia;
                masomenos=1;
            }
            while((masomenos==1&&*(fincadecopiar-1)!='\0')||
                  (masomenos==-1&&fincadecopiar!=cade-1))
            /*Muevo todo x cantidad de lugares hacia la derecha o izquierda*/
            {
                *fincadepegar=*fincadecopiar;
                fincadecopiar+=masomenos;
                fincadepegar+=masomenos;
            }
            cade-=cantpalbusc;
            while(*reem!='\0')
            {
                *cade=*reem;
                cade++;
                reem++;
            }
            reem=inireem;
        }
        else if(cantpalcade+diferencia>tam)
            return -(cantveces+1);
        busc=inibusc;
        cade++;
    }
    return cantveces;
}

size_t miStrlen(const char *cad)
{
    size_t i = 0;
    while(*(cad)!='\0')
    {
        cad++;
        i++;
    }
    return i;
}
