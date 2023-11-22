#ifndef TORNEO_H_INCLUDED
#define TORNEO_H_INCLUDED
#include "equipo.h"

typedef struct nodoTorneo
{
    equipo datoEquipo;
    struct nodoTorneo * siguiente;
}nodoTorneo;

///Prototipados
nodoTorneo * inicListaTorneo();
nodoTorneo * crearNodoTorneo(equipo dato);
nodoTorneo * agregarPpio(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
nodoTorneo * agregarEnOrdenNombre(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
nodoTorneo * agregarEnOrdenPuntos(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
void mostrarTabla(nodoTorneo* lista);

#endif // TORNEO_H_INCLUDED
