#include <stdio.h>
#include <stdlib.h>
#include "equipo.h"


void mostrar_equipo(equipo e)
{
    printf("%s",e.nombreEquipo);
    printf("%i",e.partidosJugados);
    printf("%i",e.partidosGanados);
    printf("%i",e.partidosEmpatados);
    printf("%i",e.partidosPerdidos);
    printf("%i",e.golesEquipo);
    printf("%i",e.puntosEquipo);
}


