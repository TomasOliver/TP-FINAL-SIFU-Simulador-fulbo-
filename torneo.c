#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "torneo.h"

/*
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


void mostrarTabla(nodoTorneo* lista)
{
    while(lista != NULL)
    {
        mostrar_equipo(lista->datoEquipo);
        lista= lista->siguiente;
    }
}
*/
