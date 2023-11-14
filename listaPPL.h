#ifndef LISTA_PPL_H_INCLUDED
#define LISTA_PPL_H_INCLUDED
#include "equipo.h"
#include "subLista.h"

typedef struct nodoEquipo
{
    equipo dato;
    struct nodoJugador * listaDeJugadores;
    struct nodoEquipo* siguiente;
} nodoEquipo;

///Prototipado
nodoEquipo* inicEquipo();
nodoEquipo* alta(nodoEquipo* listaPpl, equipo e, jugador j);
nodoEquipo* buscar_equipo(nodoEquipo* listaPpl,char nombreEquipo[]);
nodoEquipo* agregar_equipo(nodoEquipo* listaPpl, equipo e);
nodoEquipo* crear_nodo_equipo(equipo e);
nodoEquipo* agregar_final_equipo(nodoEquipo* lista,nodoEquipo* nuevo_nodo);
nodoEquipo* buscar_nodo_final_equipo(nodoEquipo* lista);


#endif // LISTA_PPL_H_INCLUDED
