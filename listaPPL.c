#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "listaPPL.h"

nodoEquipo* inicEquipo()
{
    return NULL;
}

nodoEquipo* alta(nodoEquipo* listaPpl, equipo e, jugador j)
{
    nodoJugador* nuevo_nodo=crear_nodo_jugador(j);

    nodoEquipo* posEquipo = buscar_equipo(listaPpl, e.nombreEquipo);

    if(posEquipo == NULL)
    {
        listaPpl = agregar_equipo(listaPpl, e);
        posEquipo = buscar_nodo_final_equipo(listaPpl);
    }

    posEquipo->listaDeJugadores = agregar_final(posEquipo->listaDeJugadores, nuevo_nodo);


    return listaPpl;
}

nodoEquipo* buscar_equipo(nodoEquipo* listaPpl,char nombreEquipo[])
{
    nodoEquipo* nodoBuscado = NULL;
    nodoEquipo* seg = listaPpl;

    while(seg !=NULL && nodoBuscado == NULL)
    {
        if(strcmp(seg->dato.nombreEquipo, nombreEquipo) == 0)
        {
            nodoBuscado = seg;
        }
        seg = seg->siguiente;
    }

    return nodoBuscado;
}

nodoEquipo* crear_nodo_equipo(equipo e)
{
    nodoEquipo* aux = (nodoEquipo*) malloc(sizeof(nodoEquipo)); //Reservo memoria para el NODO
    aux->dato = e;
    aux->siguiente = NULL;
    aux->listaDeJugadores = iniclista_jugador();
    return aux; //Retorno el nodo
}

nodoEquipo* agregar_equipo(nodoEquipo* listaPpl, equipo e)
{
    nodoEquipo* nuevoNodoEquipo = crear_nodo_equipo(e);

    listaPpl = agregar_final_equipo(listaPpl, nuevoNodoEquipo);

    return listaPpl;
}


nodoEquipo* agregar_final_equipo(nodoEquipo* lista,nodoEquipo* nuevo_nodo)
{
    nodoEquipo* seg=lista;

    if(lista==NULL)
    {
        lista=nuevo_nodo;
    }
    else
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo_nodo;
    }
    return lista;
}

nodoEquipo* buscar_nodo_final_equipo(nodoEquipo* lista)
{
    nodoEquipo* seg=lista;

    while(seg->siguiente!=NULL)
    {
        seg=seg->siguiente;
    }

    return seg;
}

int existeEquipo(nodoEquipo* listaPpl,char nombreEquipo[])
{
    int flag=0;
    nodoEquipo* seg = listaPpl;

    while(seg !=NULL && flag == 0)
    {
        if(strcmp(seg->dato.nombreEquipo, nombreEquipo) == 0)
        {
            flag=1;
        }
        seg = seg->siguiente;
    }

    return flag;
}

void AgregarJugador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores,jugador j)
{
    if(existeJugador(arbolJugadores,j.nombreJugador)==1)
    {
        printf("\nError. El jugador ya se encuentra registrado...\n");
    }
    else
    {
        int flag=0;
        char nombreEquipo[30];
        equipo e;
        mostrarNombresEquipos(listaPpl);

        while(flag==0)
        {
            printf("Ingrese el nombre del equipo donde desea registrar al jugador: \n");
            fflush(stdin);
            gets(nombreEquipo);

            if(existeEquipo(listaPpl,nombreEquipo)==0)
            {
                printf("\nError. El equipo no existe o no esta registrado. Intente nuevamente...\n");
            }
            else
            {
                flag=1;
                e=retornarEquipo(listaPpl,nombreEquipo);
            }
        }

        nodoarbol* nuevoNodo=crear_nodo_arbol(j);
        insertar_nodo_arbol(arbolJugadores,nuevoNodo);

        alta(listaPpl,e,j); //Para cargarlo en la LISTA DE LISTAS
    }
}

equipo retornarEquipo(nodoEquipo* listaPpl,char nombreEquipo[])
{
    equipo e;
    while(listaPpl!=NULL)
    {
        if(strcmp(nombreEquipo,listaPpl->dato.nombreEquipo)==0)
        {
            e=listaPpl->dato;
        }
        listaPpl=listaPpl->siguiente;
    }
    return e;
}


