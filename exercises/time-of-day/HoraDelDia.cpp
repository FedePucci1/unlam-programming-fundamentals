#include "HoraDelDia.h"

using namespace std;

HoraDelDia::HoraDelDia(int hora,int minu, int segu)
{
    this->hora=hora;
    this->minuto=minu;
    this->segundo=segu;
    if(this->segundo>=60)
    {
        this->minuto++;
        this->segundo-=60;
    }
    if(this->minuto>=60)
    {
        this->hora++;
        this->minuto-=60;
    }
    if(this->hora==24)
        this->hora=0;
}

HoraDelDia::HoraDelDia(int horarel)
{
    int horas,minu;
    while(horarel>=86400)
        horarel-=86400;
    horas=horarel/3600;
    if(horas>0)
        horarel-=horas*3600;

    if(horas==24)
        horas=0;

    minu=horarel/60;
    if(minu>0)
        horarel-=minu*60;

    this->hora=horas;
    this->minuto=minu;
    this->segundo=horarel;
}

HoraDelDia::HoraDelDia()
{
    this->hora=10;
    this->minuto=10;
    this->segundo=10;
}

HoraDelDia& HoraDelDia::operator=(HoraDelDia momento)
{
    this->hora=momento.hora;
    this->minuto=momento.minuto;
    this->segundo=momento.segundo;
    return *this;
}

HoraDelDia HoraDelDia::operator+(const HoraDelDia& momento)
{
    HoraDelDia momento1(this->hora+momento.hora,this->minuto+momento.minuto,this->segundo+momento.segundo);
    if(momento1.segundo>=60)
    {
        momento1.minuto++;
        momento1.segundo-=60;
    }
    if(momento1.minuto>=60)
    {
        momento1.hora++;
        momento1.minuto-=60;
    }
    if(momento1.hora>23)
        momento1.hora-=24;

    return momento1;
}

int HoraDelDia::operator>= (const HoraDelDia& z2) const
{
    if(this->hora == z2.hora)
    {
        if(this->minuto == z2.minuto)
            return this->segundo >= z2.segundo;
        else
            return this->minuto >= z2.minuto;
    }
    else
        return this->hora >= z2.hora;
}
int HoraDelDia::operator< (const HoraDelDia& z2) const
{
    if(this->hora == z2.hora)
    {
        if(this->minuto == z2.minuto)
            return this->segundo < z2.segundo;
        else
            return this->minuto < z2.minuto;
    }
    else
        return this->hora < z2.hora;
}

HoraDelDia HoraDelDia::operator++(int)
{
    this->segundo++;
    if(this->segundo>=60)
    {
        this->minuto++;
        this->segundo-=60;
    }
    if(this->minuto>=60)
    {
        this->hora++;
        this->minuto-=60;
    }
    if(this->hora==24)
        this->hora=0;

    HoraDelDia h1(this->hora,this->minuto,this->segundo);
    return h1;
}

HoraDelDia& HoraDelDia::operator+=(const int a)
{
    this->segundo+=a;

    if(this->segundo>=60)
    {
        this->minuto++;
        this->segundo-=60;
    }
    if(this->minuto>=60)
    {
        this->hora++;
        this->minuto-=60;
    }
    if(this->hora==24)
        this->hora=0;

    //HoraDelDia h1(this->hora,this->minuto,this->segundo);
    return *this;
}

ostream & operator<<(ostream &salida,const HoraDelDia &obj)
{
    salida << obj.hora<< ":"<< obj.minuto<< ":" << obj.segundo;
    return salida;
}

istream& operator >> (istream &i, HoraDelDia& p)
{
    i >> p.hora >> p.minuto >> p.segundo;
    i.ignore();
    return i;
}

HoraDelDia operator+(int a,HoraDelDia &obj)
{
    obj.segundo++;
    if(obj.segundo>=60)
    {
        obj.minuto++;
        obj.segundo-=60;
    }
    if(obj.minuto>=60)
    {
        obj.hora++;
        obj.minuto-=60;
    }
    if(obj.hora==24)
        obj.hora=0;

    HoraDelDia h1(obj.hora,obj.minuto,obj.segundo);
    return h1;
}

HoraDelDia HoraDelDia::getHoraMaxima()
{
    HoraDelDia h1(23,59,59);
    return h1;
}
