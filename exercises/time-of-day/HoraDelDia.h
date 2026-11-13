#ifndef HORADELDIA_H_INCLUDED
#define HORADELDIA_H_INCLUDED
#include <iostream>
#include <windows.h>

using namespace std;

class HoraDelDia
{
private:
    int hora;
    int minuto;
    int segundo;

public:

    HoraDelDia();
    HoraDelDia(int hora,int minu, int segu);
    HoraDelDia(int horarel);
    friend ostream& operator<<(ostream &sal,const HoraDelDia& hora);
    friend istream& operator>>(istream &i,HoraDelDia& p);
    HoraDelDia& operator=(HoraDelDia momento);
    HoraDelDia& operator+=(const int a);
    HoraDelDia operator+(const HoraDelDia& momento);
    HoraDelDia operator++(int);
    int operator>= (const HoraDelDia& z2) const;
    int operator< (const HoraDelDia& z2) const;
    friend HoraDelDia operator+(int,HoraDelDia &);
    static HoraDelDia getHoraMaxima();

};

#endif // HORADELDIA_H_INCLUDED
