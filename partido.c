#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "partido.h"
#include "equipo.h"

void simularPartido(equipo equipoA, equipo equipoB, partido* a, partido* b, int opcion)
{

    a->golesPartido = 0;
    b->golesPartido = 0;
    a->tarjetasPartido = 0;
    b->tarjetasPartido = 0;

    srand(time(NULL));

    int ga=0;
    int gb=0;
    int ta=0;
    int tb=0;

    for (int minuto = 1; minuto <= 90; minuto++)
    {
        if (simularGol())
        {
            if (rand() % 2 == 0)
            {
                a->golesPartido++;
                a->golesXMinuto[ga] = minuto;
                ga++;
            }
            else
            {
                b->golesPartido++;
                b->golesXMinuto[gb] = minuto;
                gb++;
            }
        }

        if (simularTarjeta())
        {
            if (rand() % 2 == 0)
            {
                a->tarjetasPartido++;
                a->tarjetasXMinuto[ta] = minuto;
                ta++;
            }
            else
            {
                b->tarjetasPartido++;
                b->tarjetasXMinuto[tb] = minuto;
                tb++;
            }
        }

        printf("\r%s %i - %2d' - %i %s",equipoA.nombreEquipo,a->golesPartido,minuto,b->golesPartido,equipoB.nombreEquipo);

        fflush(stdout);

        if(opcion == 2)
        {
            usleep(100000);
        }
    }

    printf("\n\nResultado final: %s %d - %d %s\n",equipoA.nombreEquipo, a->golesPartido, b->golesPartido, equipoB.nombreEquipo);
    printf("Tarjetas: %s %d - %d %s\n",equipoA.nombreEquipo, a->tarjetasPartido, b->tarjetasPartido, equipoB.nombreEquipo);
}

void contarPuntosYGoles(equipo* equipoA, equipo* equipoB, partido a, partido b)
{
    if(a.golesPartido > b.golesPartido)
    {
        equipoA->puntosEquipo += 3;
    }
    else if(a.golesPartido < b.golesPartido)
    {
        equipoB->puntosEquipo += 3;
    }
    else
    {
        equipoA->puntosEquipo += 1;
        equipoB->puntosEquipo += 1;
    }

    equipoA->golesEquipo += a.golesPartido;
    equipoB->golesEquipo += b.golesPartido;
}

void resumenPartido(equipo equipoA, equipo equipoB, partido a, partido b)
{
    int contGA=0;
    int contGB=0;
    int contTA=0;
    int contTB=0;

    int i=0;

    while(i<=90)
    {
        if(a.golesXMinuto[contGA]==i)
        {
            printf("\nGol de %s en el minuto %i",equipoA.nombreEquipo,a.golesXMinuto[contGA]);
            contGA++;
        }
        if(a.tarjetasXMinuto[contTA]==i)
        {
            printf("\nTarjeta de %s en el minuto %i",equipoA.nombreEquipo,a.tarjetasXMinuto[contTA]);
            contTA++;
        }
        if(b.golesXMinuto[contGB]==i)
        {
            printf("\nGol de %s en el minuto %i",equipoB.nombreEquipo,b.golesXMinuto[contGB]);
            contGB++;
        }
        if(b.tarjetasXMinuto[contTB]==i)
        {
            printf("\nTarjeta de %s en el minuto %i",equipoB.nombreEquipo,b.tarjetasXMinuto[contTB]);
            contTB++;
        }
        i++;
    }
}

// Función para simular un evento de gol con probabilidades ajustadas
int simularGol()
{
    int probabilidad = rand() % 100;

    if (probabilidad < 6)
    {
        return 1;  // Gol
    }
    else
    {
        return 0;  // Sin gol
    }
}

// Función para simular un evento de tarjeta con probabilidades ajustadas
int simularTarjeta()
{
    int probabilidad = rand() % 100;

    if (probabilidad < 5)
    {
        return 1;  // Tarjeta
    }
    else
    {
        return 0;  // Sin tarjeta
    }
}
