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

int existeJugador(nodoarbol* arbol,char nombre[])
{
    int flag=0;

    if(arbol!=NULL)
    {
        if(strcmpi(nombre,arbol->dato.nombreJugador)==0)
        {
            flag=1; //Si encuentra el dato lo retorna
        }
        else
        {
            if(strcmpi(nombre,arbol->dato.nombreJugador)>0)
            {
                flag=existeJugador(arbol->der,nombre);
            }
            else
            {
                flag=existeJugador(arbol->izq,nombre);
            }
        }
    }
    return flag; //Si NO encuentra el dato retorna NULL
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

nodoarbol* nodoMasIzquierda(nodoarbol* arbol)
{
    if(arbol)
    {
        if(arbol->izq != NULL)
        {
            arbol = nodoMasIzquierda(arbol->izq);
        }
    }
    return arbol;//si el arbol esta vacio retorna NULL
}


nodoarbol* nodoMasDerecha(nodoarbol* arbol)
{
    if(arbol)
    {
        if(arbol->der != NULL)
        {
            arbol = nodoMasDerecha(arbol->der);
        }
    }
    return arbol;
}


int esHoja(nodoarbol * arbol)
{
    int rta=0;

    if(arbol)
    {
        if(arbol->izq==NULL && arbol->der==NULL)
        {
            rta=1;
        }
    }
    return rta;
}

int esGrado1(nodoarbol * arbol)
{
    int rta=0;

    if(arbol)
    {
        if( (arbol->izq==NULL && arbol->der!=NULL) || (arbol->izq!=NULL && arbol->der==NULL) )
        {
            rta=1;
        }
    }
    return rta;
}

nodoarbol* borrarNodoArbol(nodoarbol* arbol, char nombreBuscado[])
{
    if(arbol!=NULL)  // cond corte y sol triv implicita: no hace nada y retorna arbol, que va a ser NULL)
    {
        if(strcmpi(nombreBuscado,arbol->dato.nombreJugador)>0)
        {
            arbol->der = borrarNodoArbol(arbol->der, nombreBuscado); // si el dato buscado es mayor, busca por la dcha
        }
        else if (strcmpi(nombreBuscado,arbol->dato.nombreJugador)<0)
        {
            arbol->izq = borrarNodoArbol(arbol->izq, nombreBuscado); //si el dato buscado es menor, busca por la izq
        }
        else if (strcmpi(nombreBuscado,arbol->dato.nombreJugador)==0)   // si lo encontró (si no es < ni > ni llego al final es pq lo encontró)
        {
            if(arbol->izq != NULL)          ///si tiene un izquierdo
            {
                nodoarbol* masDer = nodoMasDerecha(arbol->izq);
                arbol->dato = masDer->dato;  //al nodo a borrar le asigno como nuevo dato el del nodo mas derecho de la rama izquierda (el mas grande de los menores)
                arbol->izq = borrarNodoArbol(arbol->izq, arbol->dato.nombreJugador); //y ahora busco y borro del lado izq el nodo que "subí"
            }
            else if(arbol->der != NULL)     /// si tiene un derecho
            {
                nodoarbol* masIzq = nodoMasIzquierda(arbol->der);
                arbol->dato = masIzq->dato;  //al nodo a borrar le asigno como nuevo dato el del mas izq de la rama derecha (el mas chico de los mayores)
                arbol->der = borrarNodoArbol(arbol->der, arbol->dato.nombreJugador); //y ahora busco y borro del lado dcho el nodo que "subí"
            }
            else                         /// SI ES HOJA (no tiene izq ni der)
            {
                free(arbol);// puede ser q la hoja a borrar fuera el nodo q buscaba originariamente, o q fuera el nodo que "subi" y ahora necesito borrarlo para q no quede duplicado
                arbol = NULL; //como estamos en funcion recursiva, el otro llamado espera 1 nodo y si solo hago el free habra error
            }
        }
    }
    return arbol;
}



jugador cargar_jugador()
{
    jugador aux;

    printf("Ingrese nombre y apellido del jugador: \n");
    fflush(stdin);
    gets(aux.nombreJugador);
    ///Agregar validacion para el nombre del jugador, buscando en arbol

    printf("Ingrese nacionalidad del jugador: \n");
    fflush(stdin);
    gets(aux.nacionalidadJugador);

    printf("Ingrese calidad del jugador (entre 1 y 5): \n");
    scanf("%i",&aux.calidadJugador);
    aux=validarCalidadJugador(aux);

    printf("Ingrese edad del jugador (entre 18 y 40): \n");
    scanf("%i",&aux.edad);
    aux=validarEdadJugador(aux);

    printf("Ingrese pierna habil del jugador(Izquierda/Derecha): \n");
    fflush(stdin);
    gets(aux.piernaHabil);
    aux=validarPiernaHabilJugador(aux);

    printf("Ingrese posicion del jugador (arquero/defensor/mediocampista/delantero): \n");
    fflush(stdin);
    gets(aux.posicion);
    aux=validarPosicionJugador(aux);

    return aux;
}


jugador validarEdadJugador(jugador j)
{
    while(j.edad<18 || j.edad>40)
    {
        printf("Error, edad invalida. El minimo es 18 y el maximo es 40 años. Intente nuevamente...\n");
        fflush(stdin);
        scanf("%i",&j.edad);
    }
    return j;
}

jugador validarCalidadJugador(jugador j)
{
    while(j.calidadJugador<1 || j.calidadJugador>5)
    {
        printf("Error, valor invalido. El minimo es 1 y el maximo es 5. Intente nuevamente...\n");
        fflush(stdin);
        scanf("%i",&j.calidadJugador);
    }
    return j;
}

jugador validarPiernaHabilJugador(jugador j)
{
    while (strcmpi(j.piernaHabil, "Izquierda") != 0 && strcasecmp(j.piernaHabil, "Derecha") != 0)
    {
        printf("Error. Debe ingresar Izquierda o Derecha. Intente nuevamente...\n");
        fflush(stdin);
        gets(j.piernaHabil);
    }
    return j;
}

jugador validarPosicionJugador(jugador j)
{
    while (strcmpi(j.posicion, "Arquero")!=0 && strcasecmp(j.posicion, "Defensor")!=0 && strcmpi(j.posicion, "Mediocampista")!=0 && strcmpi(j.posicion, "Delantero")!=0)
    {
        printf("Error, posicion invalida. Intente nuevamente...\n");
        fflush(stdin);
        gets(j.posicion);
    }
    return j;
}

void mostrar_jugador(jugador a)
{
    printf("Nombre y apellido: %s\n",a.nombreJugador);
    printf("Nacionalidad: %s\n",a.nacionalidadJugador);
    printf("Calidad: %i\n",a.calidadJugador);
    printf("Edad: %i\n",a.edad);
    printf("Pierna habil: %s\n",a.piernaHabil);
    printf("Posicion: %s\n",a.posicion);

    if(a.estadoJugador==1)
    {
        printf("Estado: Activo\n\n");
    }
    else
    {
        printf("Estado: De baja\n\n");
    }
}









