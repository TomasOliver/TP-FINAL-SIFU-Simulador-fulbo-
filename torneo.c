#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "torneo.h"

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


nodoTorneo * agregarEnOrdenNombre(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo)
{
    if(lista == NULL)
    {
        lista = nuevoNodoTorneo;
    }
    else
    {
        if(strcmp(nuevoNodoTorneo->datoEquipo.nombreEquipo,lista->datoEquipo.nombreEquipo)<0)
            lista = agregarPpio(lista, nuevoNodoTorneo);
        else
        {
            nodoTorneo * ante = lista;
            nodoTorneo * seg = lista->siguiente;
            while( (seg != NULL)&&(strcmp(nuevoNodoTorneo->datoEquipo.nombreEquipo,seg->datoEquipo.nombreEquipo)>=0) )
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

nodoTorneo * agregarEnOrdenPuntos(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo)
{
    if(lista == NULL)
    {
        lista = nuevoNodoTorneo;
    }
    else
    {
        if(nuevoNodoTorneo->datoEquipo.puntosEquipo>lista->datoEquipo.puntosEquipo)
        {
            lista = agregarPpio(lista, nuevoNodoTorneo);
        }
        else if(nuevoNodoTorneo->datoEquipo.puntosEquipo == lista->datoEquipo.puntosEquipo)
        {
            if(nuevoNodoTorneo->datoEquipo.golesEquipo>lista->datoEquipo.golesEquipo)
            {
                lista = agregarPpio(lista, nuevoNodoTorneo);
            }
            else
            {
                nodoTorneo * seg = lista->siguiente;
                nuevoNodoTorneo->siguiente = seg->siguiente;
                seg = nuevoNodoTorneo;
            }
        }
        else
        {
            nodoTorneo * ante = lista;
            nodoTorneo * seg = lista->siguiente;
            while( (seg != NULL)&&(nuevoNodoTorneo->datoEquipo.puntosEquipo < seg->datoEquipo.puntosEquipo) )
            {
                ante = seg;
                seg = seg->siguiente;
            }
            if(nuevoNodoTorneo->datoEquipo.puntosEquipo == seg->datoEquipo.puntosEquipo)
            {
                if(nuevoNodoTorneo->datoEquipo.golesEquipo>seg->datoEquipo.golesEquipo)
                {
                    nuevoNodoTorneo->siguiente = seg;
                    ante->siguiente = nuevoNodoTorneo;
                }
                else
                {
                    seg->siguiente = nuevoNodoTorneo;
                    ante->siguiente = seg;
                }
            }
            else
            {
                nuevoNodoTorneo->siguiente = seg;
                ante->siguiente = nuevoNodoTorneo;
            }
        }
    }
    return lista;
}

void mostrarTorneo(fecha torneo[],int validos)
{
    int i=0;
    while(i<validos)
    {
        mostrarFecha(torneo[i]);
        i++;
    }
}

void mostrarCruce(cruce partido1)
{
    printf("\n%s vs %s\n",partido1.equipoA,partido1.equipoB);
}

void mostrarFecha(fecha aux)
{
    printf("Partido 1:");
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
