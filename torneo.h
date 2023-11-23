#ifndef TORNEO_H_INCLUDED
#define TORNEO_H_INCLUDED
#include "equipo.h"

typedef struct nodoTorneo
{
    equipo datoEquipo;
    struct nodoTorneo * siguiente;
} nodoTorneo;

typedef struct
{
    char equipoA[30];
    char equipoB[30];
} cruce;

typedef struct
{
    cruce partido1;
    cruce partido2;
    cruce partido3;
} fecha;

///Prototipados
nodoTorneo * inicListaTorneo();
nodoTorneo * crearNodoTorneo(equipo dato);
nodoTorneo * agregarPpio(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
nodoTorneo * agregarEnOrdenNombre(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
nodoTorneo * agregarEnOrdenPuntos(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
void mostrarTabla(nodoTorneo* lista);
void cargarTorneo(fecha torneo[], int dimension);
cruce cargarCruce(char nombreEquipoA[],char nombreEquipoB[]);
fecha cargarFecha(cruce partido1,cruce partido2,cruce partido3);

#endif // TORNEO_H_INCLUDED
