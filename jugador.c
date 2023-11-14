#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "jugador.h"


nodoarbol* inicArbol()
{
    return NULL;
}

nodoarbol* crear_nodo_arbol(jugador dato)
{
    nodoarbol* nuevo_nodo=(nodoarbol*) malloc(sizeof(nodoarbol));

    nuevo_nodo->dato=dato;
    nuevo_nodo->izq=NULL;
    nuevo_nodo->der=NULL;

    return nuevo_nodo;
}

nodoarbol* buscar(nodoarbol* arbol,char nombre[])
{
    nodoarbol* rta=NULL;

    if(arbol!=NULL)
    {
        if(strcmpi(nombre,arbol->dato.nombreJugador)==0)
        {
            rta=arbol; //Si encuentra el dato lo retorna
        }
        else
        {
            if(strcmpi(nombre,arbol->dato.nombreJugador)>0)
            {
                rta=buscar(arbol->der,nombre);
            }
            else
            {
                rta=buscar(arbol->izq,nombre);
            }
        }
    }
    return rta; //Si NO encuentra el dato retorna NULL
}

nodoarbol* insertar_nodo_arbol(nodoarbol* arbol,nodoarbol* nuevo_nodo)
{
    if(arbol==NULL)
    {
        arbol= nuevo_nodo;
    }
    else
    {
        if(strcmp(nuevo_nodo->dato.nombreJugador,arbol->dato.nombreJugador)>0)
        {
            arbol->der=insertar_nodo_arbol(arbol->der,nuevo_nodo);
        }
        else
        {
            arbol->izq=insertar_nodo_arbol(arbol->izq,nuevo_nodo);
        }
    }
    return arbol;
}

void preorder(nodoarbol* arbol) ///Muestro la raiz primero
{
    if(arbol!=NULL)
    {
        mostrar_jugador(arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoarbol* arbol)
{
    if(arbol!=NULL)
    {
        inorder(arbol->izq);
        mostrar_jugador(arbol->dato);
        inorder(arbol->der);
    }
}

void postorder(nodoarbol* arbol)
{
    if(arbol!=NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        mostrar_jugador(arbol->dato);

    }
}





jugador cargar_jugador()
{
    jugador aux;

    printf("Ingrese nombre y apellido del jugador: \n");
    fflush(stdin);
    gets(aux.nombreJugador);
    printf("Ingrese nacionalidad del jugador: \n");
    fflush(stdin);
    gets(aux.nacionalidadJugador);
    printf("Ingrese calidad del jugador: \n");
    scanf("%i",&aux.calidadJugador);
    printf("Ingrese edad del jugador: \n");
    scanf("%i",&aux.edad);
    printf("Ingrese pierna habil del jugador(i/d): \n");
    fflush(stdin);
    gets(aux.piernaHabil);
    printf("Ingrese posicion del jugador: \n");
    fflush(stdin);
    gets(aux.posicion);

    return aux;
}

void mostrar_jugador(jugador a)
{
    printf("Nombre y apellido: %s\n",a.nombreJugador);

    printf("Nacionalidad: %s\n",a.nacionalidadJugador);

    printf("Calidad: %i\n",a.calidadJugador);

    printf("Edad: %i\n",a.edad);

    printf("Pierna habil: %s\n",a.piernaHabil);

    printf("Posicion: %s\n\n",a.posicion);
}

