#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct
{
    int* valores;
    int posTope; //posición de nuevo tope, lugar en donde se almacenará el nuevo valor
} Pila;

void apilar(Pila * p, int valor);
int desapilar(Pila * p);
int tope(Pila * p);
int pilaVacia(Pila * p);
void mostrar(Pila * p);
void leer (Pila * p);
void inicPila(Pila * p);
void cargandoInicio();

#endif // PILA_H_INCLUDED
