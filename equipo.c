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

void mostrarDatosEquipo(equipo e)
{
    printf("\nNombre: %s\n",e.nombreEquipo);
    printf("\nCalidad: %i\n",e.calidadEquipo);
    if(e.estadoEquipo==1)
    {
        printf("\nEstado %s\n","De alta");

    }
    else
    {
        printf("\nEstado %s\n","De baja");
    }
}

equipo validarCalidadEquipo(equipo e)
{
    while(e.calidadEquipo<1 || e.calidadEquipo>5)
    {
        printf("Error, valor invalido. El minimo es 1 y el maximo es 5. Intente nuevamente...\n");
        fflush(stdin);
        scanf("%i",&e.calidadEquipo);
    }
    return e;
}




