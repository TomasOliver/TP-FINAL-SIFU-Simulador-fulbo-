#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED

///Estructuras

typedef struct
{
    char nombreEquipo[50];
    char nacionalidadEquipo[50];
    int calidadEquipo;
    int puntosEquipo;
    int golesEquipo;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
}equipo;



#endif // EQUIPO_H_INCLUDED
