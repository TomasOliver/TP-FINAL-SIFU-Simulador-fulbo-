#ifndef SUB_LISTA_H_INCLUDED
#define SUB_LISTA_H_INCLUDED
#include "jugador.h"

///Estructuras
typedef struct nodoJugador
{
    jugador dato;
    struct nodoJugador* siguiente;

}nodoJugador;
///Prototipado
nodoJugador* iniclista_jugador();
nodoJugador* cargar_nodos_al_principio_jugador(nodoJugador* lista);
nodoJugador* crear_nodo_jugador(jugador a);
nodoJugador* agregar_principio(nodoJugador* lista, nodoJugador* nuevo_nodo);
nodoJugador* insertar_nodo_ordenado(nodoJugador* lista, nodoJugador* nuevo_nodo);
nodoJugador* agregar_final(nodoJugador* lista,nodoJugador* nuevo_nodo);
nodoJugador* borrar_nodo(nodoJugador* lista,char nombre_buscado[]);
int buscar_jugador_lista(nodoJugador* lista,char nombre[]); ///Verifica si existe
nodoJugador* buscar_nodo_jugador_lista(nodoJugador* lista,char nombre[]); ///Retorna puntero al nodo
nodoJugador* invertir_elementos_lista(nodoJugador* lista);
void mostrar_lista_jugadores(nodoJugador* lista);
void buscarYmostrarJugador(nodoJugador* lista,char nombre[]);

#endif // SUB_LISTA_H_INCLUDED
