#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "torneo.h"

void guardarFechasJugadasEnTorneo(fecha torneo[],int validos,int fechasJugadas)
{
    int i=0;
    while(i<validos)
    {
        torneo[i].fechasJugadas=fechasJugadas;
        i++;
    }
}

void cargarTorneo(fecha torneo[], int dimension)
{
    char equipoA[30];
    char equipoB[30];
    char equipoC[30];
    char equipoD[30];
    char equipoE[30];
    char equipoF[30];
    cruce partido1;
    cruce partido2;
    cruce partido3;

    int i=0;
    while(i<dimension)
    {
        printf("\nCARGAR FECHA %i\n",(i+1));

        printf("Ingrese nombre del equipo 1: \n");
        fflush(stdin);
        gets(equipoA);

        printf("Ingrese nombre del equipo 2: \n");
        fflush(stdin);
        gets(equipoB);

        partido1=cargarCruce(equipoA,equipoB);

        printf("Ingrese nombre del equipo 3: \n");
        fflush(stdin);
        gets(equipoC);

        printf("Ingrese nombre del equipo 4: \n");
        fflush(stdin);
        gets(equipoD);

        partido2=cargarCruce(equipoC,equipoD);

        printf("Ingrese nombre del equipo 5: \n");
        fflush(stdin);
        gets(equipoE);

        printf("Ingrese nombre del equipo 6: \n");
        fflush(stdin);
        gets(equipoF);

        partido3=cargarCruce(equipoE,equipoF);

        torneo[i].partido1=partido1;
        torneo[i].partido2=partido2;
        torneo[i].partido3=partido3;
        torneo[i].fechasJugadas=0;

        i++;
    }
}

cruce cargarCruce(char nombreEquipoA[],char nombreEquipoB[])
{
    cruce aux;

    strcpy(aux.equipoA,nombreEquipoA);
    strcpy(aux.equipoB,nombreEquipoB);

    return aux;
}

fecha cargarFecha(cruce partido1,cruce partido2,cruce partido3)
{
    fecha aux;

    aux.partido1=partido1;
    aux.partido2=partido2;
    aux.partido3=partido3;

    return aux;
}

nodoTorneo * inicListaTorneo()
{
    return NULL;
}

nodoTorneo * crearNodoTorneo(equipo dato)
{
    nodoTorneo * aux = (nodoTorneo*) malloc(sizeof(nodoTorneo));
    aux->datoEquipo= dato;
    aux->siguiente = NULL;
    return aux;
}

nodoTorneo * agregarPpio(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo)
{
    if(lista == NULL)
    {
        lista = nuevoNodoTorneo;
    }
    else
    {
        nuevoNodoTorneo->siguiente = lista;
        lista = nuevoNodoTorneo;
    }
    return lista;
}

nodoTorneo* agregarEnOrdenPuntos(nodoTorneo* lista, nodoTorneo* nuevoNodoTorneo)
{
    if (lista == NULL)
    {
        lista = nuevoNodoTorneo;
    }
    else
    {
        if (nuevoNodoTorneo->datoEquipo.puntosEquipo > lista->datoEquipo.puntosEquipo ||
                (nuevoNodoTorneo->datoEquipo.puntosEquipo == lista->datoEquipo.puntosEquipo &&
                 nuevoNodoTorneo->datoEquipo.golesEquipo > lista->datoEquipo.golesEquipo))
        {
            lista = agregarPpio(lista, nuevoNodoTorneo);
        }
        else
        {
            nodoTorneo* ante = lista;
            nodoTorneo* seg = lista->siguiente;

            while ((seg != NULL) &&
                    ((nuevoNodoTorneo->datoEquipo.puntosEquipo < seg->datoEquipo.puntosEquipo) ||
                     ((nuevoNodoTorneo->datoEquipo.puntosEquipo == seg->datoEquipo.puntosEquipo) &&
                      (nuevoNodoTorneo->datoEquipo.golesEquipo < seg->datoEquipo.golesEquipo))))
            {
                ante = seg;
                seg = seg->siguiente;
            }

            nuevoNodoTorneo->siguiente = seg;
            ante->siguiente = nuevoNodoTorneo;
        }
    }
    return lista;
}

nodoTorneo* borrarTodaLaLista(nodoTorneo * lista)
{
    nodoTorneo* proximo;
    nodoTorneo* seg;
    seg = lista;
    while(seg != NULL)
    {
        proximo = seg->siguiente;//tomo la dir del siguiente.
        free(seg);//borro el actual.
        seg = proximo;//actualizo el actual con la dir del siguiente, para avanzar
    }
    return seg;
}

void mostrarTorneo(fecha torneo[],int validos)
{
    int i=0;
    while(i<validos)
    {
        printf("\nFecha %i: \n",i+1);
        mostrarFecha(torneo[i]);
        i++;
    }
}

void mostrarCruce(cruce partido1)
{
    printf("\n%s vs %s\n\n",partido1.equipoA,partido1.equipoB);
}

void mostrarFecha(fecha aux)
{
    printf("\nPartido 1:");
    mostrarCruce(aux.partido1);
    printf("Partido 2:");
    mostrarCruce(aux.partido2);
    printf("Partido 3:");
    mostrarCruce(aux.partido3);
}


void mostrarTabla(nodoTorneo* lista)
{
    while(lista != NULL)
    {
        mostrar_equipo(lista->datoEquipo);
        lista= lista->siguiente;
    }
}

void tablaPuntos(nodoTorneo * lista)
{
    // ESQUINAS //
    gotoxy(25,7);
    printf("*");
    gotoxy(76,7);
    printf("*");

    gotoxy(25,21);
    printf("*");
    gotoxy(76,21);
    printf("*");

    // Linea Superior //

    for(int i=26; i<76; i++)
    {
        gotoxy(i,7);
        printf("-");

        gotoxy(i,9);
        printf("-");
    }

    // Linea Izquierda //

    for(int k=8; k<21; k++)
    {
        gotoxy(25,k);
        printf("|");
    }


    // Linea Derecha //
    for(int l=8; l<21; l++)
    {
        gotoxy(76,l);
        printf("|");

    }

    // Linea Inferior//
    for(int j=26; j<76; j++)
    {
        gotoxy(j,21);
        printf("-");
    }

    // Lineas del Medio verticales //
    for(int l=8; l<21; l++)
    {
        gotoxy(70,l);
        printf("|");

        gotoxy(65,l);
        printf("|");

        gotoxy(60,l);
        printf("|");

        gotoxy(55,l);
        printf("|");

        gotoxy(50,l);
        printf("|");

        gotoxy(45,l);
        printf("|");

        gotoxy(29,l);
        printf("|");
    }

    // ENCABEZADO //
    gotoxy(32,8);
    printf("EQUIPOS");

    gotoxy(27,8);
    printf("P");

    gotoxy(47,8);
    printf("PJ");

    gotoxy(52,8);
    printf("PG");

    gotoxy(57,8);
    printf("PE");

    gotoxy(62,8);
    printf("PP");

    gotoxy(67,8);
    printf("GF");

    gotoxy(72,8);
    printf("PTS");

    //Nombre EQUIPOS//

    int i = 10;
    int p = 1;

    while(lista != NULL)
    {

        gotoxy(27,i);
        printf("%i",p);

        gotoxy(31,i);
        printf("%s",lista->datoEquipo.nombreEquipo);

        gotoxy(47,i);
        printf("%i",lista->datoEquipo.partidosJugados);

        gotoxy(52,i);
        printf("%i",lista->datoEquipo.partidosGanados);

        gotoxy(57,i);
        printf("%i",lista->datoEquipo.partidosEmpatados);

        gotoxy(62,i);
        printf("%i",lista->datoEquipo.partidosPerdidos);

        gotoxy(67,i);
        printf("%i",lista->datoEquipo.golesEquipo);

        gotoxy(73,i);
        printf("%i",lista->datoEquipo.puntosEquipo);

        i += 2;
        p++;
        lista=lista->siguiente;
    }
}
