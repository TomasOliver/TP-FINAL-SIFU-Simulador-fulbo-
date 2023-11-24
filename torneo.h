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
    int fechasJugadas;
} fecha;

///Prototipados
nodoTorneo * inicListaTorneo();
nodoTorneo * crearNodoTorneo(equipo dato);
nodoTorneo * agregarPpio(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
nodoTorneo * agregarEnOrdenPuntos(nodoTorneo * lista, nodoTorneo * nuevoNodoTorneo);
void mostrarTabla(nodoTorneo* lista);
void cargarTorneo(fecha torneo[], int dimension);
cruce cargarCruce(char nombreEquipoA[],char nombreEquipoB[]);
fecha cargarFecha(cruce partido1,cruce partido2,cruce partido3);
void mostrarTorneo(fecha torneo[],int validos);
void mostrarCruce(cruce partido1);
void mostrarFecha(fecha aux);
void guardarFechasJugadasEnTorneo(fecha torneo[],int validos,int fechasJugadas);
nodoTorneo* borrarTodaLaLista(nodoTorneo * lista);

#endif // TORNEO_H_INCLUDED
