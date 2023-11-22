#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED

///Estructuras

typedef struct
{
    char nombreEquipo[50];
    int calidadEquipo;
    int puntosEquipo;
    int golesEquipo;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int estadoEquipo; //1 activo - 0 de baja
}equipo;



#endif // EQUIPO_H_INCLUDED
