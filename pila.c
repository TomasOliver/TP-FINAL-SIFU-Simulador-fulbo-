#include <stdio.h>
#include <stdlib.h>
#include "pila.h"


void inicPila(Pila * p)
{
    p->valores=(int*) malloc(sizeof(int)*100);
    p->posTope=0;
}

void apilar(Pila * p, int valor)
{
    if(p->posTope<100)
    {
        p->valores[p->posTope]=valor;
        p->posTope++;
    }
    else
    {
        printf("\nLa pila esta llena...");
    }
}

int desapilar(Pila* A)
{
    int desapilado= -99999; // no hay solucion perfecta...
    if(A->posTope >0)
    {
        desapilado = A->valores[A->posTope-1];
        (A->posTope)--;
    }
    else
        printf("\nLa pila ya esta vacia, se retornará -99999\n");

    return desapilado;
}

int tope(Pila* A)
{
    int topeA= -99999; // no hay solucion perfecta...
    if(A->posTope >0)
    {
        topeA = A->valores[(A->posTope)-1];
    }
    else
    {
        printf("\nLa pila ya esta vacia, se retornará -99999\n");
    }

    return topeA;
}

int pilaVacia(Pila* A)
{
    int flag=0;

    if (A->posTope==0)
    {
        flag=1;
    }

    return flag;
}

void mostrar(Pila* A)
{
    int i;
    if(A->posTope > 0)
    {
        printf("\nBase------------------------------Tope\n");

        for(i=0; i<A->posTope; i++)
        {
            printf("| %d |",A->valores[i]);
        }
        printf("\nBase------------------------------Tope\n");
    }
    else
        printf("\nLa pila esta vacia\n");
}

void leer(Pila * p)
{
    int valor;
    if (p->posTope < 100)
    {
        printf("\nIngrese un valor: \n");
        scanf("%i",&valor);
        p->valores[p->posTope]=valor;
        p->posTope++;
    }
    else
    {
        printf("La pila ya está llena");
    }
}

void cargandoInicio()///funcion para simular carga
{
    Pila miPila;
    inicPila(&miPila);
    int i = 0;

    apilar(&miPila, 100);
    apilar(&miPila, 75);
    apilar(&miPila, 55);
    apilar(&miPila, 40);
    apilar(&miPila, 25);
    apilar(&miPila, 10);
    apilar(&miPila, 5);
    apilar(&miPila, 0);

    int elemento;
    while(!pilaVacia(&miPila))
    {
        elemento = desapilar(&miPila);
        gotoxy(38, 10);
        printf("Guardando datos:\n");
        gotoxy(54, 10);
        printf("%i%%", elemento);
        usleep(500000);
        system("cls");
    }

    printf("\n");
}
