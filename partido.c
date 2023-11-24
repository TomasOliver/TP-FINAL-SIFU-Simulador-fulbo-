#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "partido.h"
#include "equipo.h"
#include "gotoxy.h"

void simularPartido(equipo equipoA, equipo equipoB, partido* x, int opcion)
{

    x->golesEquipoA = 0;
    x->golesEquipoB = 0;
    x->tarjetasEquipoA = 0;
    x->tarjetasEquipoB = 0;

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
                x->golesEquipoA++;
                x->golesXMinutoEquipoA[ga] = minuto;
                ga++;
            }
            else
            {
                x->golesEquipoB++;
                x->golesXMinutoEquipoB[gb] = minuto;
                gb++;
            }
        }

        if (simularTarjeta())
        {
            if (rand() % 2 == 0)
            {
                x->tarjetasEquipoA++;
                x->tarjetasXMinutoEquipoA[ta] = minuto;
                ta++;
            }
            else
            {
                x->tarjetasEquipoB++;
                x->tarjetasXMinutoEquipoB[tb] = minuto;
                tb++;
            }
        }

        fflush(stdout);

        if(opcion == 2)
        {
            cuadroPartido();

            gotoxy(15,2);
            printf("%s",equipoA.nombreEquipo);
            gotoxy(41,2);
            printf("%i",x->golesEquipoA);

            gotoxy(54,2);
            printf("%i",x->golesEquipoB);
            gotoxy(70,2);
            printf("%s",equipoB.nombreEquipo);

            gotoxy(47,2);
            printf("%2d'",minuto);

            usleep(100000);
        }
        else if(opcion==1)
        {
            gotoxy(33,2);
            printf("%s %i - %2d' - %i %s",equipoA.nombreEquipo,x->golesEquipoA,minuto,x->golesEquipoB,equipoB.nombreEquipo);
        }
    }

    //printf("\n\nResultado final: %s %d - %d %s\n",equipoA.nombreEquipo, x->golesEquipoA, x->golesEquipoB, equipoB.nombreEquipo);
    //printf("Tarjetas: %s %d - %d %s\n",equipoA.nombreEquipo, x->tarjetasEquipoA, x->tarjetasEquipoB, equipoB.nombreEquipo);
}

void contarPuntosYGoles(equipo* equipoA, equipo* equipoB, partido x)
{
    if(x.golesEquipoA > x.golesEquipoB)
    {
        equipoA->puntosEquipo += 3;
        equipoA->partidosGanados += 1;
        equipoB->partidosPerdidos += 1;
    }
    else if(x.golesEquipoA < x.golesEquipoB)
    {
        equipoB->puntosEquipo += 3;
        equipoB->partidosGanados += 1;
        equipoA->partidosPerdidos += 1;
    }
    else
    {
        equipoA->puntosEquipo += 1;
        equipoB->puntosEquipo += 1;

        equipoA->partidosEmpatados += 1;
        equipoB->partidosEmpatados += 1;

    }

    equipoA->golesEquipo += x.golesEquipoA;
    equipoB->golesEquipo += x.golesEquipoB;

    equipoA->partidosJugados += 1;
    equipoB->partidosJugados += 1;
}

void resumenPartido(equipo equipoA, equipo equipoB, partido x)
{
    int contGA=0;
    int contGB=0;
    int contTA=0;
    int contTB=0;

    int i=0;
    int g=0;

    while(i<=90)
    {
        if(x.golesXMinutoEquipoA[contGA]==i)
        {
            gotoxy(6,5+g);
            printf("Gol de %s en el minuto %i",equipoA.nombreEquipo,x.golesXMinutoEquipoA[contGA]);
            contGA++;
            g++;
        }
        if(x.tarjetasXMinutoEquipoA[contTA]==i)
        {
            gotoxy(6,5+g);
            printf("Tarjeta de %s en el minuto %i",equipoA.nombreEquipo,x.tarjetasXMinutoEquipoA[contTA]);
            contTA++;
            g++;
        }
        if(x.golesXMinutoEquipoB[contGB]==i)
        {
            gotoxy(56,5+g);
            printf("Gol de %s en el minuto %i",equipoB.nombreEquipo,x.golesXMinutoEquipoB[contGB]);
            contGB++;
            g++;
        }
        if(x.tarjetasXMinutoEquipoB[contTB]==i)
        {
            gotoxy(56,5+g);
            printf("Tarjeta de %s en el minuto %i",equipoB.nombreEquipo,x.tarjetasXMinutoEquipoB[contTB]);
            contTB++;
            g++;
        }
        i++;
    }
}

// Función para simular un evento de gol con probabilidades ajustadas
int simularGol()
{
    int probabilidad = rand() % 100;

    if (probabilidad < 4)
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


void cuadroPartido()
{
    // ESQUINAS //
    gotoxy(0,0);
    printf("*");
    gotoxy(0,25);
    printf("*");
    gotoxy(99,0);
    printf("*");
    gotoxy(99,25);
    printf("*");

    for(int i=1; i<99; i++)
    {
        gotoxy(i,0);
        printf("-");
    }

    for(int i=1; i<99; i++)
    {
        gotoxy(i,3);
        printf("-");
    }

    for(int l=1; l<25; l++)
    {
        gotoxy(99,l);
        printf("|");
    }

    for(int l=1; l<25; l++)
    {
        gotoxy(48,l);
        printf("|");
    }

    for(int j=1; j<99; j++)
    {
        gotoxy(j,25);
        printf("-");
    }

    for(int k=1; k<25; k++)
    {
        gotoxy(0,k);
        printf("|");
    }

}


