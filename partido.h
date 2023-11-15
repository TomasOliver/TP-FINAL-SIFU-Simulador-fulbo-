#ifndef PARTIDO_H_INCLUDED
#define PARTIDO_H_INCLUDED
#include "equipo.h"

///Estructuras

typedef struct
{
    int golesPartido;
    int tarjetasPartido;
    int golesXMinuto[20];
    int tarjetasXMinuto[20];

}partido;

///Prototipado
void simularPartido(equipo equipoA, equipo equipoB, partido a, partido b, int opcion);
void resumenPartido(equipo equipoA, equipo equipoB, partido a, partido b);
void contarPuntosYGoles(equipo* equipoA, equipo* equipoB, partido a, partido b);
int simularGol();
int simularTarjeta();


#endif // PARTIDO_H_INCLUDED
