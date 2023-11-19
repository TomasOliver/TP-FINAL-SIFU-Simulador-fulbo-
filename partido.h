#ifndef PARTIDO_H_INCLUDED
#define PARTIDO_H_INCLUDED
#include "equipo.h"

///Estructuras

typedef struct
{
    int golesEquipoA;
    int golesEquipoB;
    int tarjetasEquipoA;
    int tarjetasEquipoB;
    int golesXMinutoEquipoA[20];
    int golesXMinutoEquipoB[20];
    int tarjetasXMinutoEquipoA[20];
    int tarjetasXMinutoEquipoB[20];

}partido;

///Prototipado
void simularPartido(equipo equipoA, equipo equipoB, partido* x, int opcion);
void resumenPartido(equipo equipoA, equipo equipoB, partido x);
void contarPuntosYGoles(equipo* equipoA, equipo* equipoB, partido x);
int simularGol();
int simularTarjeta();


#endif // PARTIDO_H_INCLUDED
