#include <stdio.h>
#include <stdlib.h>
#include "equipo.h"


void mostrar_equipo(equipo e)
{
    printf("\n%s\n",e.nombreEquipo);
    printf("Partidos Jugados: %i\n",e.partidosJugados);
    printf("Partidos Ganados: %i\n",e.partidosGanados);
    printf("Partidos Empatados: %i\n",e.partidosEmpatados);
    printf("Partidos Perdidos: %i\n",e.partidosPerdidos);
    printf("Goles a favor: %i\n",e.golesEquipo);
    printf("Puntos: %i\n\n",e.puntosEquipo);
}


