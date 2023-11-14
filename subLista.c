#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "subLista.h"

nodoJugador* iniclista_jugador()
{
    return NULL;
}

nodoJugador* cargar_nodos_al_principio_jugador(nodoJugador* lista)
{
    jugador aux;
    nodoJugador* nuevo_nodo;
    char continuar='s';

    while(continuar=='s')
    {
        aux=cargar_jugador();

        nuevo_nodo = crear_nodo_jugador(aux); //Creo el nodo, le asigno espacio en memoria y guardo en el puntero la direccion de memoria

        lista = agregar_principio(lista,nuevo_nodo);

        printf("Desea continuar (s/n): ");
        fflush(stdin);
        scanf("%c",&continuar);
        printf("\n");
    }
    return lista;
}

nodoJugador* crear_nodo_jugador(jugador a)
{
    nodoJugador* aux = (nodoJugador*) malloc(sizeof(nodoJugador)); //Reservo memoria para el NODO
    aux->dato=a;
    aux->siguiente=NULL;
    return aux; //Retorno el nodo
}

nodoJugador* agregar_principio(nodoJugador* lista, nodoJugador* nuevo_nodo)
{
    if(lista==NULL) //Si esta vacia
    {
        lista=nuevo_nodo; //Primer nodo
    }
    else //Si NO esta vacia
    {
        nuevo_nodo->siguiente=lista; //Engancho nuevo con la lista
        lista=nuevo_nodo; //Nuevo_nodo es el nuevo inicio de la lista
    }
    return lista; //Retorno el NUEVO INICIO DE LA LISTA
}

int buscar_jugador_lista(nodoJugador* lista,char nombre[])
{
    int flag=0;

    while(lista!=NULL && flag==0)
    {
        if(strcmp(lista->dato.nombreJugador,nombre)==0)
        {
            flag=1;
        }
        lista=lista->siguiente;
    }
    return flag;
}

nodoJugador* insertar_nodo_ordenado(nodoJugador* lista, nodoJugador* nuevo_nodo)
{
    if(lista==NULL)
    {
        lista=nuevo_nodo;
    }
    else if(strcmp(lista->dato.nombreJugador,nuevo_nodo->dato.nombreJugador)>0)
    {
        lista=agregar_principio(lista,nuevo_nodo);
    }
    else
    {
        nodoJugador* ante = lista;
        nodoJugador* seg = lista->siguiente;
        while(seg != NULL && strcmp(nuevo_nodo->dato.nombreJugador,seg->dato.nombreJugador)>0)
        {
            ante=seg;
            seg=seg->siguiente;
        }
        nuevo_nodo->siguiente=seg;
        ante->siguiente=nuevo_nodo;
    }
    return lista;
}

nodoJugador* agregar_final(nodoJugador* lista,nodoJugador* nuevo_nodo)
{
    nodoJugador* seg=lista;
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

nodoJugador* borrar_nodo(nodoJugador* lista,char nombre_buscado[])
{
    nodoJugador* a_borrar;
    if(lista!=NULL)
    {
        if(strcmp(nombre_buscado,lista->dato.nombreJugador)==0)
        {
            a_borrar=lista;
            lista=lista->siguiente;
            free(a_borrar);
        }
        else
        {
            nodoJugador* ante=lista;
            nodoJugador* seg=lista->siguiente;
            while(seg!=NULL && strcmp(nombre_buscado,seg->dato.nombreJugador)!=0)
            {
                ante=seg;
                seg=seg->siguiente;
            }
            if(seg!=NULL)
            {
                ante->siguiente=seg->siguiente;
                free(seg);
            }
        }
    }
    return lista;
}

nodoJugador* invertir_elementos_lista(nodoJugador* lista)
{
    nodoJugador* ante=NULL;
    nodoJugador* seguidora=lista;

    nodoJugador* sig;


    while(seguidora!=NULL)
    {
        sig=seguidora->siguiente;
        seguidora->siguiente=ante;
        ante=seguidora;
        seguidora=sig;

    }
    lista=ante;
    return lista;
}

void mostrar_lista_jugadores(nodoJugador* lista)
{
    while(lista !=NULL)
    {
        mostrar_jugador(lista->dato);
        lista=lista->siguiente;
    }
}
